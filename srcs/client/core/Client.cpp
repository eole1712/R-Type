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

Client::Client(int port)
{
  _nm = new NetManager;
  _nc = new NetClient(port, _nm, this);
  _packetHandlerFuncs = {
    [this] (APacket* packet, unsigned int id) {
      ServerConnexionPacket* pack = dynamic_cast<ServerConnexionPacket*>(packet);
      if (pack == NULL)
	return;
    },
    [this] (APacket* packet, unsigned int id) {
      ServerGameInfoPacket* pack = dynamic_cast<ServerGameInfoPacket*>(packet);
      if (pack == NULL)
	return;
    },
    [this] (APacket* packet, unsigned int id) {
      ServerGameConnectPacket* pack = dynamic_cast<ServerGameConnectPacket*>(packet);
      if (pack == NULL)
	return;
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
}

void Client::handlePacket(APacket* pack, unsigned int id)
{
  _packetHandlerFuncs[pack->getType()](pack, id);
}
