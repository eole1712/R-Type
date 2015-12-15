#include "ClientConnexionPacket.hpp"
#include "ClientGameInfoPacket.hpp"
#include "ClientGameConnectPacket.hpp"
#include "Thread.hpp"
#include "Server.hpp"




Server::Server() {
	_netManager = new NetManager();
	_netServer = new NetServer(kPort, _netManager, this);

	std::vector<std::function<void(APacket* packet, unsigned int id) > > _packetHandlerFuncs = {
		[] (APacket* packet, unsigned int id) {
			ClientConnexionPacket* pack = dynamic_cast<ClientConnexionPacket*>(packet);
			if (pack == NULL)
				return;
			ServerConnexionPacket ret();
			if (_users.find(id) != _users.end())
			{
				ret.setServerString("Not Welcome to R-Type Server");
				ret.setStatus(false);
			}
			_players[id] = new User(pack->getName(), id);
			ret.setServerString("Welcome to R-Type Server");
			ret.setStatus(true);
			_netServer.send(ret, id);
		},
		[] (APacket* packet, unsigned int id) {
			ClientGameInfoPacket* pack = dynamic_cast<ClientGameInfoPacket*>(packet);
			if (pack == NULL)
				return;
			if (_users.find(id) != _users.end())
				return;
			for (auto& game : _games) {
				ServerGameInfoPacket ret();
				ret.setRoomId(game.getID());
				ret.setRoomSlots(4 - game.getNbPlayers());
				ret.setRoomName(game.getName());
				_netServer.send(ret, id);
			}
		},
		[] (APacket* packet, unsigned int id) {
			ClientGameConnectPacket* pack = dynamic_cast<ClientGameConnectPacket*>(packet);
			static unsigned int gameID = 1;
			if (pack == NULL)
				return;
			if (_users.find(id) != _users.end())
				return;
			IGame* game;
			if ((auto it  = _games.find(pack->getRoomId())) == _games.end())
			{
				_games[gameID] = new Game(gameID, pack->getRoomName());
				game = _games[gameID];
				++gameID;
			}
			else
				game = *it;
			ServerGameConnectPacket ret();
			if (!game->addPlayer(_users[id])) {
				ret.setStatus(false);
			}
			else {
				ret.setStatus(true);
				ret.setPlayerId(_users[id]->getPlayer()->getColor());
			}
			_netServer.send(ret, id);
		},
		[] (APacket* packet, unsigned int id) {
			ClientKeyboardPressPacket* pack = dynamic_cast<ClientKeyboardPressPacket*>(packet);
			if (pack == NULL)
				return;
			if (_users.find(id) != _users.end())
				return;
			IGame* game = _games[user->getGameID()];
			User* user = _users[id];
			std::pair<unsigned int, bool> key = pack->getStatus();
			if (!game->isInGame()) {
				if (key.first = 5 && key.second == 1)
					user->setReady(!user->isReady());
				bool startGame = true;
				for (auto& aUser : game->getUsers())
				{
					if (!user->isReady())
					startGame = false;
				}
				if (startGame)
					startGame(game);
				return;
			}
			if (key.first < 4)
				user->getPlayer()->setMoving(key.first, key.second);
			else
				user->getPlayer()->setShooting(key.second);
		} 
	};
}

Server::~Server() {
	delete _netServer;
	delete _netManager;
}

void	Server::start() {
	std::function<void(std::nullptr_t)> fptr = [this] (std::nullptr_t) {
		_netManager->loop();
	};
	Thread<std::nullptr_t> t(fptr, nullptr);
}

void Server::startGame(IGame* game) {
	std::function<void(std::nullptr_t)> fptr = [game] (std::nullptr_t) {
		while (game->nextAction());
	};
	Thread<std::nullptr_t> t(fptr, nullptr);
}

void	Server::handlePacket(APacket* packet, unsigned int id) {
	_packetHandlerFuncs[packet->getType() - APacket::kNbServerPackets](packet, id);
}	