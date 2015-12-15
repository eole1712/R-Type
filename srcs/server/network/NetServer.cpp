#include "NetServer.hpp"

NetServer::NetServer(int port, NetManager* manager, IPacketHandler* handler)
  : Networker(port, manager, handler)
{}

NetServer::~NetServer()
{}

void NetServer::sendAll(APacket * pack)
{
  int id = 0;
  for (auto& peer : _peers) {
    send(pack, id);
    ++id;
  }
}
