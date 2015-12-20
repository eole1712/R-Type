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
	std::cout << "Connected ! : dayPhrase : " << pack->getServerString() << std::endl;

//	//Debug feature
//	std::cout << "Test feature : sending create room packet with room + this addr" << std::endl;
//	//ClientGameConnectPacket* ansPack = new ClientGameConnectPacket; #useless
//	std::stringstream name;
//	name << "room" << reinterpret_cast<unsigned long>(this);
//	this->createGame(name.str());
//	//end Debug feature
      }
    },

    [this] (APacket* packet, unsigned int id) {
      ServerGameInfoPacket* pack = dynamic_cast<ServerGameInfoPacket*>(packet);
      if (pack == NULL)
	return;
      std::cout << "got game info from server : " << pack->getRoomName() << std::endl;
      _rooms[pack->getRoomName()] = pack->getRoomId();
      _menu->addGame(pack->getRoomId(), pack->getRoomName(), pack->getRoomSlots(), pack->getRoomName());
    },
    [this] (APacket* packet, unsigned int id) {
      ServerGameConnectPacket* pack = dynamic_cast<ServerGameConnectPacket*>(packet);
      if (pack == NULL)
	return;
      if (pack->getStatus()) {
	std::cout << "Connecting to a game with id : " << static_cast<unsigned int>(pack->getPlayerId()) << std::endl;
	_playerId = pack->getPlayerId();
	//	_menu->startGame();
	std::cout << "game started" << std::endl;
      }
      else
	std::cout << "failed to connect" << std::endl;
    },

    [this] (APacket* packet, unsigned int id) {
      ServerPlayerMovePacket* pack = dynamic_cast<ServerPlayerMovePacket*>(packet);
      if (pack == NULL)
	return;

    },

    [this] (APacket* packet, unsigned int id) {
      ServerPingPacket* pack = dynamic_cast<ServerPingPacket*>(packet);
      if (pack == NULL)
	return;
    },

    [this] (APacket* packet, unsigned int id) {
      ServerUnitSpawnPacket* pack = dynamic_cast<ServerUnitSpawnPacket*>(packet);
      if (pack == NULL)
	return;
      if (_game)
	{
	  _game->connectUnit(static_cast<Unit::typeID>(pack->getUnitType()), pack->getX(), pack->getY(), pack->getUnitID(), pack->getTimer(), pack->getParam());
	}
      // if (_game)
      // 	{
      // 	  _units.push_back(new Unit::AUn:it(pack->getX(), pack->getY(), pack->getUnitID(), pack->getTimer());
      // 	  _game->connectUnit(_units.back());
      // 	}
    },

    [this] (APacket* packet, unsigned int id) {
      ServerUnitDiePacket* pack = dynamic_cast<ServerUnitDiePacket*>(packet);
      if (pack == NULL)
	return;
      // if (_game)
      // 	{
      // 	  _units.remove_if([pack] (Unit::AUnit const& unit) {
      // 	    return unit.getID() == pack->getUnitID();
      // 	  });
      // 	  _game->disconnectUnit(pack->getUnitID());
      // 	}
    },

    [this] (APacket* packet, unsigned int id) {
      ServerTimerRefreshPacket* pack = dynamic_cast<ServerTimerRefreshPacket*>(packet);
      if (pack == NULL)
	return;
      if (_game == nullptr)
        _menu->startGame();
      else
        _game->setTimer(pack->getCurrentTimer());
      std::cout << "timer update" << std::endl;
    }
  };
  _menu = new Menu(1600, 800, this);
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
  std::cout << "main view init" << std::endl;
  _menu->initMainView();
  std::cout << "finished" << std::endl;
  t.join();
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

void Client::selectGame(const std::string &name)
{
  ClientGameConnectPacket pack;

  pack.setRoomName(name);
  pack.setRoomId(_rooms[name]);
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

IGameHandler* Client::getGameHandler()
{
  return this;
}
