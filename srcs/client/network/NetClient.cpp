#include "ClientConnexionPacket.hpp"
#include "NetClient.hpp"

NetClient::NetClient(int port, NetManager* manager, IPacketHandler* handler)
  : Networker(port, manager, handler)
{

}

NetClient::~NetClient()
{

}

void NetClient::connect(std::string const& addr, int port, std::string const& name)
{
  ClientConnexionPacket* pack;

  _peers.push_back(std::make_pair(addr, port));
  pack = new ClientConnexionPacket();
  pack->setClientName(name);
  sendPacket(pack);
}

void NetClient::sendPacket(APacket *packet)
{
  send(packet, 0);
}
