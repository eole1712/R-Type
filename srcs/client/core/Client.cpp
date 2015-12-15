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

Client::Client(int port)
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
      }
    },
    [this] (APacket* packet, unsigned int id) {
      ServerGameInfoPacket* pack = dynamic_cast<ServerGameInfoPacket*>(packet);
      if (pack == NULL)
	return;
      _rooms[pack->getRoomName()] = pack->getRoomId();
      _menu->addGame(pack->getRoomName(), pack->getRoomSlots(), pack->getRoomName());
    },
    [this] (APacket* packet, unsigned int id) {
      ServerGameConnectPacket* pack = dynamic_cast<ServerGameConnectPacket*>(packet);
      if (pack == NULL)
	return;
      if (pack->getStatus()) {
	_playerId = pack->getPlayerId();

      }
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
    },
    [this] (APacket* packet, unsigned int id) {
      ServerUnitDiePacket* pack = dynamic_cast<ServerUnitDiePacket*>(packet);
      if (pack == NULL)
	return;
    },
    [this] (APacket* packet, unsigned int id) {
      ServerTimerRefreshPacket* pack = dynamic_cast<ServerTimerRefreshPacket*>(packet);
      if (pack == NULL)
	return;
    }
  };
  _menu = new Menu(720, 480, this);
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

void Client::selectGame(const std::string &name)
{
  ClientGameConnectPacket* pack = new ClientGameConnectPacket;

  pack->setRoomName(name);
  pack->setRoomId(_rooms[name]);
  _nc->sendPacket(pack);
}

void Client::handlePacket(APacket* pack, unsigned int id)
{
  _packetHandlerFuncs[pack->getType()](pack, id);
}

void Client::setGame(Game* game)
{
  _game = game;
}

void Client::sendKey()
{
  ;
}
