#include "ClientConnexionPacket.hpp"
#include "ClientGameInfoPacket.hpp"
#include "ClientGameConnectPacket.hpp"
#include "ServerConnexionPacket.hpp"
#include "ServerGameConnectPacket.hpp"
#include "ServerGameInfoPacket.hpp"
#include "ServerUnitSpawnPacket.hpp"
#include "ServerUnitDiePacket.hpp"
#include "ServerTimerRefreshPacket.hpp"
#include "ClientKeyboardPressPacket.hpp"
#include "ServerPlayerMovePacket.hpp"
#include "Thread.hpp"
#include "Server.hpp"
#include "GameUtils.hpp"
#include "MonsterFactory.hpp"
#include "MissileFactory.hpp"



Server::Server() {
	_netManager = new NetManager();
	_netServer = new NetServer(kPort, _netManager, this);
	_packetHandlerFuncs = {
		[this] (APacket* packet, unsigned int id) {
			std::cout << "ping received" << std::endl;
		},
		[this] (APacket* packet, unsigned int id) {
			ClientConnexionPacket* pack = dynamic_cast<ClientConnexionPacket*>(packet);
			if (pack == NULL)
				return;
			ServerConnexionPacket ret;
			std::cout << "Client connect with id : " << id << std::endl;
			if (_users.find(id) != _users.end())
			{
				ret.setServerString("Not Welcome to R-Type Server");
				ret.setStatus(false);
			}
			else {
				_users[id] = new User(pack->getClientName(), id);
				ret.setServerString("Welcome to R-Type Server");
				ret.setStatus(true);
			}
			_netServer->send(&ret, id);
		},
		[this] (APacket* packet, unsigned int id) {
			ClientGameInfoPacket* pack = dynamic_cast<ClientGameInfoPacket*>(packet);
			if (pack == NULL)
				return;
			if (_users.find(id) == _users.end())
				return;
			sendRoomStatus(id);
		},
		[this] (APacket* packet, unsigned int id) {
			ClientGameConnectPacket* pack = dynamic_cast<ClientGameConnectPacket*>(packet);
			static unsigned int gameID = 1;
			std::cout << "in ClientGameConnect ! " << std::endl;
			if (pack == NULL)
				return;
			std::cout << "pack is well formated" << std::endl;
			if (_users.find(id) == _users.end())
				return;

          //Recherche ou création de la game
			IGame* game;
			auto it  = _games.find(pack->getRoomId());
			if ((it) == _games.end())
			{
				std::cout << "creating game" << std::endl;
				_games[gameID] = new Game(gameID, pack->getRoomName(), this);
				game = _games[gameID];
				++gameID;
			}
			else
				game = (*it).second;
			ServerGameConnectPacket ret;
			User* user = _users[id];
			if (user->isInGame())
			{
				int currentGameID = user->getGameID();
				_games[currentGameID]->removePlayer(user->getPlayer()->getColor());
				ret.setStatus(false);
				ret.setGameId(0);
				ret.setPlayerId(0);
				user->setReady(false);
				sendToUser(&ret, id);
				if (currentGameID == game->getID())
				{
					sendRoomStatus();
					return;
				}	
			}
			if (!game->addPlayer(_users[id])) {
				std::cerr << "Game [" << game->getID() << "] cowardly refused to add player" << std::endl; 
				ret.setStatus(false);
				ret.setGameId(0);
				ret.setPlayerId(0);
			}
			else {
				ret.setStatus(true);
				ret.setGameId(game->getID());
				ret.setPlayerId(_users[id]->getPlayer()->getID());
			}
			sendToUser(&ret, id);
			sendRoomStatus();
		},
		[this] (APacket* packet, unsigned int id) {
			ClientKeyboardPressPacket* pack = dynamic_cast<ClientKeyboardPressPacket*>(packet);
			if (pack == NULL)
				return;
			if (_users.find(id) == _users.end())
				return;
			User* user = _users[id];
			std::pair<unsigned int, bool> key = pack->getStatus();
			if (!user->isInGame())
				return;
			if (!(_games[user->getGameID()]->isStarted()))
			{
				IGame* game = _games[user->getGameID()];
				if (key.first == 4 && key.second == 1)
				{
					user->setReady(!user->isReady());
					sendRoomStatus();
				}
				
				bool shouldStart = true;
				for (auto& aUser : game->getUsers())
				{
					if (!aUser->isReady())
						shouldStart = false;
				}
				if (shouldStart)
				{
					refreshTimer(game->getID());
					startGame(game);
				}
			}
			else if (key.first < 4)
				user->getPlayer()->setMoving(static_cast<Unit::dir>(key.first), key.second);
			else
				user->getPlayer()->setShooting(key.second);
		}
	};
}

Server::~Server() {
	delete _netServer;
	delete _netManager;
	Monster::Factory::destroy();
	Unit::Missile::Factory::destroy();
}

void	Server::start() {
	std::function<void(std::nullptr_t)> fptr = [this] (std::nullptr_t) {
		_netManager->loop();
	};
	Thread<std::nullptr_t> t(fptr, nullptr);
	t.join();
}

void Server::startGame(IGame* game) {
	std::function<void(std::nullptr_t)> fptr = [this, game] (std::nullptr_t) {
		static unsigned int     refresh = 1;
		unsigned int            gameID = game->getID();

        //Boucle du jeu principale.
		game->start();
		while (game->nextAction()) {
			std::vector<User*> v = game->getUsers();

            //refreshTimer(game->getID());
			if (GameUtils::Game::now(gameID) > (refresh * 1000))
			{
				refreshTimer(gameID);
				refresh++;
			}
			Timer::time                       time = GameUtils::Game::now(gameID);
            //refreshPlayersPosition
			for (auto& user : v) {
				if (user->needRefresh()) {
					ServerPlayerMovePacket packet;
					packet.setPlayerID(user->getPlayer()->getID());
					packet.setX(user->getPlayer()->getX(time));
					packet.setY(user->getPlayer()->getY(time));

					sendToGame(&packet, gameID);
					user->setRefresh(false);
				}
			}
		}
	};
	Thread<std::nullptr_t> t(fptr, nullptr);
}

void	Server::handlePacket(APacket* packet, unsigned int id) {
	_packetHandlerFuncs[packet->getType() - 7](packet, id);
}

void    Server::refreshTimer(unsigned int idGame)
{
	ServerTimerRefreshPacket   pack;

	pack.setCurrentTimer(GameUtils::Game::now(idGame));
	sendToGame(&pack, idGame);
}

void        Server::sendUnit(Unit::AUnit *unit, unsigned int unitType)
{
	ServerUnitSpawnPacket    pack;

	pack.setTimer(unit->getCreationTime());
	pack.setX(unit->getStartX());
	pack.setY(unit->getStartY());
	pack.setUnitType(unitType);
	pack.setUnitID(unit->getID());
	pack.setParam(unit->getTeam() == Unit::ALLY ? 1000 : -1000);

	sendToGame(&pack, unit->getGameID());
}

void        Server::killUnit(unsigned int id, unsigned int gameID)
{
	ServerUnitDiePacket    pack;

	pack.setUnitID(id);

	sendToGame(&pack, gameID);
}

void Server::sendToUser(APacket* packet, int userId) {
	_netServer->send(packet, userId);
}

void Server::sendToGame(APacket* packet, int gameId) {
	for(auto& user : _games[gameId]->getUsers())
	{
		sendToUser(packet, user->getClientID());
	}
}

void Server::sendToAll(APacket* packet) {
	for(auto& user : _users)
	{
		sendToUser(packet, user.second->getClientID());
	}
}

void Server::sendRoomStatus() {
	for (auto& game : _games) {
		ServerGameInfoPacket ret;
		ret.setRoomId(game.second->getID());
		ret.setRoomSlots(game.second->getNbPlayers());
		int nb = 0;
		for (auto& user : game.second->getUsers())
		{
			if (user->isReady())
				nb++;
		}
		ret.setRoomReady(nb);
		ret.setRoomName(game.second->getName());

		for (auto& user : _users) {
			ret.setUserReady(user.second->isReady());
			sendToUser(&ret, user.second->getClientID());
		}
	}
}

void Server::sendRoomStatus(int userId) {
	for (auto& game : _games) {
		ServerGameInfoPacket ret;
		ret.setRoomId(game.second->getID());
		ret.setRoomSlots(game.second->getNbPlayers());
		int nb = 0;
		for (auto& user : game.second->getUsers())
		{
			if (user->isReady())
				nb++;
		}
		ret.setRoomReady(nb);
		ret.setRoomName(game.second->getName());

		ret.setUserReady(_users.find(userId)->second->isReady());
		sendToUser(&ret, userId);
	}
}