#include "ClientConnexionPacket.hpp"
#include "NetClient.hpp"

#ifndef _WIN32
#include <arpa/inet.h>
#endif
#include <iostream>

NetClient::NetClient(int port, NetManager* manager, IPacketHandler* handler)
  : Networker(port, manager, handler), _current(0)
{

}

NetClient::~NetClient()
{

}

void NetClient::connect(std::string const& addr, int port, std::string const& name)
{
  ClientConnexionPacket* pack;
  unsigned int id = 0;
  std::string locAddr = addr;

  if (addr == "0")
    locAddr = "127.0.0.1";
  for (auto& elem : _peers) {
      if (std::get<peerInd::port>(elem.second) == port &&
	  inet_addr(std::get<peerInd::addr>(elem.second).c_str()) == inet_addr(locAddr.c_str())) {
       break;
     }
     ++id;
   }
  _peers[id] = std::make_tuple(locAddr, port, getCurTime());
  std::cout << "sending to : " << locAddr << ":" << port << std::endl;
  pack = new ClientConnexionPacket();
  pack->setClientName(name);
  send(pack, id);
}

void NetClient::setServer(int id)
{
  _current = id;
  std::cout << "current server id : " << id << std::endl;
}

void NetClient::sendPacket(APacket *packet)
{
  std::cout << "send to : " << _current << std::endl;
  send(packet, _current);
}
