#include "Networker.hpp"
#include "UdpSocket.hpp"
#include "ServerGameInfoPacket.hpp"
#include "ClientGameInfoPacket.hpp"
#include "ServerGameConnectPacket.hpp"
#include "ClientGameConnectPacket.hpp"
#include "ClientConnexionPacket.hpp"
#include "ServerConnexionPacket.hpp"
#include "ServerPlayerMovePacket.hpp"
#include "ServerTimerRefreshPacket.hpp"
#include "ServerUnitDiePacket.hpp"
#include "ServerUnitSpawnPacket.hpp"
#include "ServerPingPacket.hpp"
#include <iostream>

std::function<void(ISocket*, std::string&, ISocket::receiveHandler)> Networker::_asyncRec = std::bind(&ISocket::async_receive, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

std::vector<std::function<APacket*(std::string const&) > > const Networker::_packHandlers = {
  [] (std::string const& data) {
    return new ServerConnexionPacket(data);
  },
  [] (std::string const& data) {
    return new ServerGameInfoPacket(data);
  },
  [] (std::string const& data) {
    return new ServerGameConnectPacket(data);
  },
  [] (std::string const& data) {
    return new ServerPlayerMovePacket(data);
  },
  [] (std::string const& data) {
    return new ServerPingPacket(data);
  },
  [] (std::string const& data) {
    return new ServerUnitSpawnPacket(data);
  },
  [] (std::string const& data) {
    return new ServerUnitDiePacket(data);
  },
  [] (std::string const& data) {
    return new ServerTimerRefreshPacket(data);
  },
  [] (std::string const& data) {
    return new ClientConnexionPacket(data);
  },
  [] (std::string const& data) {
    return new ClientGameInfoPacket(data);
  },
  [] (std::string const& data) {
    return new ClientGameConnectPacket(data);
  }
};

Networker::Networker(int port)
: _sock(new UdpSocket(port))
{

  _buffer.resize(APacket::kMaxPacketSize);
  _handle = [this] (ISocket::returnCode ret, size_t sizeRec, std::string addr, int port) {
    std::cout << "Message received from : " << addr << ":" << port << " ==> " << _buffer << std::endl;
    _packHandlers[APacket::sGetType(_buffer)](_buffer);
    _asyncRec(_sock, _buffer, _handle);
  };
  _asyncRec(_sock, _buffer, _handle);
}

Networker::Networker(int port, NetManager* manager, IPacketHandler* handler)
: _sock(new UdpSocket(port, "", manager))
{
  _PacketHandler = handler;
  _buffer.resize(APacket::kMaxPacketSize);
  _handle = [this] (ISocket::returnCode ret, size_t sizeRec, std::string addr, int port) {
    APacket* pack;
    bool found = false;
    unsigned int id = 0;

    std::cout << "Message received from : " << addr << ":" << port << " ==> " << _buffer << std::endl;
    pack = _packHandlers[APacket::sGetType(_buffer)](_buffer);
    _packList.push_front(pack);
    for (auto elem : _peers) {
      if (elem.second == port && elem.first == addr)
      {
       found = true;
       break;
     }
     ++id;
   }
   if (!found)
    _peers.push_back(std::make_pair(addr, port));
  //answer(pack, id);
  _PacketHandler->handlePacket(pack, id);
  _asyncRec(_sock, _buffer, _handle);
};
_asyncRec(_sock, _buffer, _handle);
}

Networker::~Networker()
{

}

void Networker::send(APacket *pack, int id)
{
  std::string data = pack->getData();
  unsigned long dataSize = data.size();

  _sock->setSendPort(_peers[id].second);
  _sock->setAddr(_peers[id].first);

  _sock->async_send(data, [dataSize] (ISocket::returnCode ret, size_t written) {
    if (written != dataSize || ret != ISocket::Sucess)
      std::cerr << "Error while writing ==> written : " << written << "expected : " << dataSize << " ret : " << ret << std::endl;
  });
}

APacket* Networker::getLastPacket()
{
  if (_packList.empty())
    return nullptr;

  APacket* ret = _packList.back();

  _packList.pop_back();
  return ret;
}

void Networker::answer(APacket* pack, int id)
{
  ServerConnexionPacket* srvPack;

  std::cout << "type : " << static_cast<int>(pack->getType()) << std::endl;
  std::cout << "id : " << id << std::endl;
  if (pack->getType() == 1) {
    std::cout << "answering to : " << _peers[id].first << ":" << _peers[id].second << std::endl;
    srvPack = new ServerConnexionPacket;
    srvPack->setServerString("Coucou, bienvenue chez les poneys !");
    srvPack->setStatus(true);
    srvPack->setId(0);
    send(srvPack, id);
  }
}
