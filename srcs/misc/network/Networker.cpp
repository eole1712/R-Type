#include "Networker.hpp"
#include "UdpSocket.hpp"
#include "ClientConnexionPacket.hpp"
#include "ServerConnexionPacket.hpp"
#include <iostream>

std::function<void(ISocket*, std::string&, ISocket::receiveHandler)> Networker::_asyncRec = std::bind(&ISocket::async_receive, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

std::vector<std::function<APacket*(std::string const&) > > const Networker::_packHandlers = {
  [] (std::string const& data) {
    ServerConnexionPacket* pack = new ServerConnexionPacket(data);
    std::cout << "ServerConnection ==> status : " << pack->getStatus() << " mdj : " << pack->getServerString() << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ClientConnexionPacket* pack = new ClientConnexionPacket(data);
    std::cout << "clientConnection ==> name : " << pack->getClientName() << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    std::cout << "in packet 3" << std::endl;
    return new APacket(data);
  },
  [] (std::string const& data) {
    std::cout << "in packet 4" << std::endl;
    return new APacket(data);
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

Networker::Networker(int port, NetManager* manager)
  : _sock(new UdpSocket(port, "", manager))
{
  _buffer.resize(APacket::kMaxPacketSize);
  _handle = [this] (ISocket::returnCode ret, size_t sizeRec, std::string addr, int port) {
    APacket* pack;
    bool found = false;
    int id = 0;

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
    answer(pack, id);
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
  int dataSize = data.size();

  _sock->setSendPort(_peers[id].second);
  _sock->setAddr(_peers[id].first);

  _sock->async_send(data, [dataSize] (ISocket::returnCode ret, size_t written) {
    if (written != dataSize || ret != ISocket::Sucess)
      std::cerr << "Error while writing ==> written : " << dataSize << " ret : " << ret << std::endl;
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
