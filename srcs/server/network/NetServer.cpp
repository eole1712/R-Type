#include "NetServer.hpp"

NetServer::NetServer(int port, NetManager* manager)
  : Networker(port, manager)
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
