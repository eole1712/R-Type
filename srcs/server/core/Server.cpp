#include "ClientConnexionPacket.hpp"
#include "ClientGameInfoPacket.hpp"
#include "ClientGameConnectPacket.hpp"
#include "ServerConnexionPacket.hpp"
#include "ServerGameConnectPacket.hpp"
#include "ServerGameInfoPacket.hpp"
#include "ClientKeyboardPressPacket.hpp"
#include "ServerPlayerMovePacket.hpp"
#include "Thread.hpp"
#include "Server.hpp"
#include "MonsterFactory.hpp"
#include "MissileFactory.hpp"



Server::Server() {
	_netManager = new NetManager();
	_netServer = new NetServer(kPort, _netManager, this);
	_packetHandlerFuncs = {
		[this] (APacket* packet, unsigned int id) {
			ClientConnexionPacket* pack = dynamic_cast<ClientConnexionPacket*>(packet);
			if (pack == NULL)
				return;
			ServerConnexionPacket* ret = new ServerConnexionPacket;
			std::cout << "Client connect with id : " << id << std::endl;
			if (_users.find(id) != _users.end())
			{
				ret->setServerString("Not Welcome to R-Type Server");
				ret->setStatus(false);
			}
			else {
			  _users[id] = new User(pack->getClientName(), id);
			  ret->setServerString("Welcome to R-Type Server");
			  ret->setStatus(true);
			}
			_netServer->send(ret, id);
			delete ret;
		},
		[this] (APacket* packet, unsigned int id) {
			ClientGameInfoPacket* pack = dynamic_cast<ClientGameInfoPacket*>(packet);
			if (pack == NULL)
				return;
			if (_users.find(id) == _users.end())
				return;
			for (auto& game : _games) {
                ServerGameInfoPacket* ret = new ServerGameInfoPacket;
                ret->setRoomId(game.second->getID());
				ret->setRoomSlots(4 - game.second->getNbPlayers());
                int nb = 0;
                for (auto& user : game.second->getUsers())
                {
                    if (user->isReady())
                        nb++;
                }
                ret->setRoomReady(nb);
				ret->setRoomName(game.second->getName());
				_netServer->send(ret, id);
				delete ret;
			}
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
		      _games[gameID] = new Game(gameID, pack->getRoomName());
		      game = _games[gameID];
		      ++gameID;
		    }
		  else
		    game = (*it).second;
          
          //???
		  ServerGameConnectPacket* ret = new ServerGameConnectPacket;
		  if (!game->addPlayer(_users[id])) {
		    std::cout << "failed" << std::endl;
		    ret->setStatus(false);
		  }
		  else {
		    ret->setStatus(true);
		    ret->setPlayerId(_users[id]->getPlayer()->getID());
		  }
		  std::cout << "answering packet" << std::endl;
		  _netServer->send(ret, id);
		  delete ret;
		},
		[this] (APacket* packet, unsigned int id) {
			ClientKeyboardPressPacket* pack = dynamic_cast<ClientKeyboardPressPacket*>(packet);
			if (pack == NULL)
				return;
			if (_users.find(id) == _users.end())
				return;
            User* user = _users[id];
			IGame* game = _games[user->getGameID()];
			std::pair<unsigned int, bool> key = pack->getStatus();
			if (!game->isInGame()) {
    			if (key.first == 4 && key.second == 1)
					user->setReady(!user->isReady());
				bool shouldStart = true;
				for (auto& aUser : game->getUsers())
				{
					if (!aUser->isReady())
					shouldStart = false;
				}
				if (shouldStart)
					startGame(game);
				return;
			}
			if (key.first < 4)
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
		while (game->nextAction()) {
			std::vector<User*> v = game->getUsers();
			for (auto& user : v) {
				if (user->needRefresh()) {
					ServerPlayerMovePacket* packet = new ServerPlayerMovePacket();
					packet->setPlayerID(user->getPlayer()->getID());
					packet->setX(user->getPlayer()->getX());
					packet->setY(user->getPlayer()->getY());
					for (auto& aUser : v) {
						_netServer->send(packet, aUser->getClientID());
					}
					delete packet;
					user->setRefresh(false);
				}

			}
		}
	};
	Thread<std::nullptr_t> t(fptr, nullptr);
}

void	Server::handlePacket(APacket* packet, unsigned int id) {
	_packetHandlerFuncs[packet->getType() - 8](packet, id);
}
