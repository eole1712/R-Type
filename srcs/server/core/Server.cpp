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
#include "ServerPingPacket.hpp"
#include "Thread.hpp"
#include "Server.hpp"
#include "GameUtils.hpp"
#include "MonsterFactory.hpp"
#include "MissileFactory.hpp"



Server::Server() {
	_netManager = new NetManager();
	_netServer = new NetServer(kPort, _netManager, this);
	_packetHandlerFuncs = {
        //PACKET PING
		[this] (APacket* packet, unsigned int id) {
		ServerPingPacket * pack = dynamic_cast<ServerPingPacket*>(packet);
	    if (pack == NULL)
	      return;
	    std::cout << "ping received" << std::endl;
	    if (pack->getStatus()) {
	      ServerPingPacket ans;

	      ans.setStatus(false);
	      _netServer->send(&ans, id);
	    }
	    _netServer->setTimeout(id);
		},
        
        //PACKET CONNECTION CLIENT
		[this] (APacket* packet, unsigned int id) {
			ClientConnexionPacket* pack = dynamic_cast<ClientConnexionPacket*>(packet);
			if (pack == NULL)
				return;
			ServerConnexionPacket ret;
			if (userExists(id))
			{
				ret.setServerString("Not Welcome to R-Type Server (User Already exists).");
				ret.setStatus(false);
			}
			else {
				_users[id] = new User(pack->getClientName(), id);
				ret.setServerString("Welcome to R-Type Server");
				ret.setStatus(true);
			}
			sendToUser(&ret, id);
		},
        
        //PACKET CLIENT GAME INFO
		[this] (APacket* packet, unsigned int id) {
			ClientGameInfoPacket* pack = dynamic_cast<ClientGameInfoPacket*>(packet);
			if (!userExists(id) || pack == NULL)
				return;
            std::lock_guard<Lock>   l(_lockEnd);
			sendRoomStatus(id);
		},
        
        //PACKET GAME CONNECT PACKET
		[this] (APacket* packet, unsigned int id) {
			ClientGameConnectPacket* pack = dynamic_cast<ClientGameConnectPacket*>(packet);
			if (!userExists(id) || pack == NULL)
				return;

          //Recherche ou création de la game
			IGame* game;
            
            std::lock_guard<Lock>   l(_lockEnd);
            
			auto it  = _games.find(pack->getRoomId());
			if ((it) == _games.end())
				game = createGame(pack->getRoomName());
			else
				game = (*it).second;
			ServerGameConnectPacket ret;
			User* user = _users[id];
			_netServer->setTimeout(id);
			if (user->isInGame())
			{
				int currentGameID = user->getGameID();
				for (auto& aUser : _games[currentGameID]->getUsers())
				{
					aUser.second->setReady(false);					
				}
				_games[currentGameID]->removePlayer(user->getPlayer()->getColor());
				ret.setStatus(false);
				ret.setGameId(0);
				ret.setPlayerId(0);
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
        
        //PACKET CLIENT KEYBOARD PRESS
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
            
            std::lock_guard<Lock>   l(_lockEnd);
            
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
        std::cout << "Je suis " << __FUNCTION__ << " et je cree un thread" << std::endl;
	Thread<std::nullptr_t> t(fptr, nullptr);
	#ifndef NO_PING
	Thread<std::nullptr_t> ping(std::bind(&Networker::pingFunction, _netServer, std::placeholders::_1), nullptr);
	ping.join();
	#endif
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
            
            std::unique_lock<Lock>      l(_lock);
            for (unsigned int dc : _disconnectedID)
            {
                std::map<int, User*>::iterator  it = _users.find(dc);
                if (it != _users.end()) {
                    Unit::Player *player = (*it).second->getPlayer();
                    if (player)
                    {
                        player->setAlive(false);
                        game->removePlayer(player->getColor());
                    }
                    delete (*it).second;
                    _users.erase(it);
                }
            }
            _disconnectedID.clear();
            l.unlock();
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
        refreshTimer(gameID, true);
        
        std::lock_guard<Lock>       l(_lockEnd);
        _games.erase(gameID);
        delete game;
    };
        std::cout << "Je suis " << __FUNCTION__ << " et je cree un thread" << std::endl;
	Thread<std::nullptr_t> t(fptr, nullptr);
}

void	Server::handlePacket(APacket* packet, unsigned int id) {
	_packetHandlerFuncs[packet->getType() - 7](packet, id);
}

void    Server::refreshTimer(unsigned int idGame, bool end)
{
	ServerTimerRefreshPacket   pack;

    pack.setCurrentTimer(end ? 0 : GameUtils::Game::now(idGame));
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
            if (user.second->getGameID() == game.second->getID()) ret.setUserReady(user.second->isReady());
            else ret.setUserReady(false);
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

bool Server::userExists(int userId) const {
	return (_users.find(userId) != _users.end());
}

IGame*	Server::createGame(std::string const& gameName) {
	static unsigned int gameID = 1;
	Game* ret;

	ret = new Game(gameID, gameName, this);
	_games[gameID++] = ret;
	return ret;
}

void Server::disconnectPlayer(unsigned int id)
{
    std::lock_guard<Lock>   l(_lock);

    _disconnectedID.push_back(id);
    std::cout << "player with id :" << id << "hung up" << std::endl;
}
