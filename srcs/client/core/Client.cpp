#include "Client.hpp"
#include "Thread.hpp"
#include "ServerUnitDiePacket.hpp"
#include "ServerGameInfoPacket.hpp"
#include "ServerConnexionPacket.hpp"
#include "ServerPlayerMovePacket.hpp"
#include "ServerUnitSpawnPacket.hpp"
#include "ServerGameConnectPacket.hpp"
#include "ServerTimerRefreshPacket.hpp"
#include "ServerPingPacket.hpp"
#include "ClientConnexionPacket.hpp"
#include "ClientGameConnectPacket.hpp"
#include "ClientGameInfoPacket.hpp"
#include "AUnit.hpp"
//Debug feature
#include <sstream>

Client::Client(int port)
: _connected(0)
{
    _nm = new NetManager;
    _nc = new NetClient(port, _nm, this);
    _packetHandlerFuncs = {
        [this] (APacket* packet, unsigned int id) {
            ServerConnexionPacket* pack = dynamic_cast<ServerConnexionPacket*>(packet);
            if (pack == NULL)
                return;
            if (pack->getStatus()) {
	      std::string msg = "Connected ! : dayPhrase : " + pack->getServerString();
	      std::cout << msg << std::endl;
	      _menu->setMessage(msg, false);
	      _nc->setServer(id);
	    }
	    else {
	      std::string msg = "Failed to connect ! Erreur : " + pack->getServerString();
	      _menu->setMessage(msg, true);
	    }

        },
        [this] (APacket* packet, unsigned int id) {
            ServerGameInfoPacket* pack = dynamic_cast<ServerGameInfoPacket*>(packet);
            if (pack == NULL)
                return;
//            std::cout << "got game info from server : " << pack->getRoomName() << std::endl;
            _menu->addGame(pack->getRoomId(), pack->getRoomName(), pack->getRoomSlots(), pack->getRoomReady(), pack->getRoomName(), pack->getUserReady());
        },
        [this] (APacket* packet, unsigned int) {
            ServerGameConnectPacket* pack = dynamic_cast<ServerGameConnectPacket*>(packet);
	    std::lock_guard<Lock> l(_lock);

	    if (pack == NULL)
	      return;
	    if (pack->getStatus()) {
	      std::stringstream ss;
	      ss << "Connecting to a game with id : " << static_cast<unsigned int>(pack->getPlayerId());
	      _menu->setMessage(ss.str(), false);
	      _playerId = pack->getPlayerId();
	      _connected = pack->getGameId();
	    }
	    else if (_connected != 0) {
                _connected = 0;
            }
            else
	      _menu->setMessage("Failed to connect to game", true);
	    //refreshGames();
        },

        [this] (APacket* packet, unsigned int) {
            ServerPlayerMovePacket* pack = dynamic_cast<ServerPlayerMovePacket*>(packet);
            if (pack == NULL)
                return;
            Unit::Player* pl;
            if ((pl = _game->getPlayer(pack->getPlayerID()))) {
                pl->setX(pack->getX());
                pl->setY(pack->getY());
            }
        },
        [this] (APacket* packet, unsigned int) {
            ServerUnitSpawnPacket* pack = dynamic_cast<ServerUnitSpawnPacket*>(packet);
            if (pack == NULL)
                return;
            if (_game) {
                _game->connectUnit(static_cast<Unit::typeID>(pack->getUnitType()), pack->getX(), pack->getY(), pack->getUnitID(), static_cast<Time::stamp>(pack->getTimer()), pack->getParam());
            }
            else {
                _toCreate.push_back(std::make_tuple(static_cast<Unit::typeID>(pack->getUnitType()), pack->getX(), pack->getY(), pack->getUnitID(), pack->getTimer(), pack->getParam()));
            }
        },

        [this] (APacket* packet, unsigned int) {
            ServerUnitDiePacket* pack = dynamic_cast<ServerUnitDiePacket*>(packet);
            if (pack == nullptr)
                return;
            if (_game != nullptr)
                _game->disconnectUnit(pack->getUnitID());
        },

        [this] (APacket* packet, unsigned int id) {
            ServerTimerRefreshPacket* pack = dynamic_cast<ServerTimerRefreshPacket*>(packet);
            if (pack == nullptr)
                return;
	    _nc->setTimeout(id);
	    if (_game == nullptr) {
                _menu->startGame(static_cast<Time::stamp>(pack->getCurrentTimer()));
            }
            else {
                if (_game->getTimer() > 0 && pack->getCurrentTimer() == 0)
                {
		  _connected = 0;
		  _game->setFinish();
		  _game = nullptr;
		  return ;
                }
                _game->setTimer(static_cast<Time::stamp>(pack->getCurrentTimer()));
                while (!_toCreate.empty()) {
                    _game->connectUnit(std::get<0>(_toCreate.back()), std::get<1>(_toCreate.back()), std::get<2>(_toCreate.back()), std::get<3>(_toCreate.back()), std::get<4>(_toCreate.back()), static_cast<int>(std::get<5>(_toCreate.back())));
                    _toCreate.pop_back();
                }
            }
        },

        [this] (APacket* packet, unsigned int id) {
            ServerPingPacket* pack = dynamic_cast<ServerPingPacket*>(packet);
            if (pack == NULL)
                return;
	    if (id != _nc->getCurrent())
	      return ;
	      //            std::cout << "pinged by server" << std::endl;
	    if (pack->getStatus()) {
	      ServerPingPacket ans;

	      ans.setStatus(false);
	      _nc->sendPacket(&ans);
	    }
	    _nc->setTimeout(id);
        }
    };
    _menu = new Menu(1200, 800, this);
    _game = nullptr;
}

Client::~Client()
{
    delete _nm;
    delete _nc;
}

void Client::start()
{
    std::function<void(std::nullptr_t)> fptr = [this] (std::nullptr_t) {
        _nm->loop();
    };
    std::cout << "Je suis " << __FUNCTION__ << " et je cree un thread" << std::endl;
    Thread<std::nullptr_t> t(fptr, nullptr);
    #ifndef NO_PING
    Thread<std::nullptr_t> ping(std::bind(&Networker::pingFunction, _nc, std::placeholders::_1), nullptr);
    #endif
    std::cout << "main view init" << std::endl;
    _menu->initMainView();
    std::cout << "finished" << std::endl;
    #ifndef NO_PING
    _nc->stopPing();
    ping.join();
    #endif
    _nm->stop();
    t.join();
    std::cout << "Game finished" << std::endl;
}

void Client::connect(const std::string &ip, const std::string &name)
{
    std::cout << "connecting to : " << ip << "with name : " << name << std::endl;
    _nc->connect(ip, 6524, name);
}

void Client::refreshGames()
{
    ClientGameInfoPacket pack;
    std::cout << "Trying to refresh game list." << std::endl;
    _nc->sendPacket(&pack);
}

void Client::selectGame(const std::string &name, int id)
{
    ClientGameConnectPacket pack;

    pack.setRoomName(name);
    pack.setRoomId(id);
    _nc->sendPacket(&pack);
}

void Client::createGame(const std::string &name)
{
    ClientGameConnectPacket pack;

    pack.setRoomId(0);
    pack.setRoomName(name);
    _nc->sendPacket(&pack);
}

void Client::handlePacket(APacket* pack, unsigned int id)
{
    _packetHandlerFuncs[pack->getType()](pack, id);
}

void Client::setGame(Game* game)
{
    _game = game;
}

void Client::sendKey(ClientKeyboardPressPacket::keyEvent e)
{
    ClientKeyboardPressPacket packet(e);

    _nc->sendPacket(&packet);
}

void Client::disconnectPlayer(unsigned int id)
{
  _connected = 0;
  if (_game) {
    _game->setFinish();
    _game = nullptr;
  }

  std::cout << "server with id : " << id << "hung up" << std::endl;;
}

uint32_t Client::getRoomConnected()
{
	std::lock_guard<Lock> l(_lock);
	return _connected;
}

IGameHandler* Client::getGameHandler()
{
    return this;
}
