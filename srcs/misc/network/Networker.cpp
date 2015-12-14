#include "Networker.hpp"
#include "UdpSocket.hpp"
#include <iostream>

std::function<void(ISocket*, std::string&, ISocket::receiveHandler)> Networker::_asyncRec = std::bind(&ISocket::async_receive, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

std::vector<std::function<APacket*(std::string const&) > > const Networker::_packHandlers = {
  [] (std::string const& data) {
    std::cout << "in packet 1" << std::endl;
    return new APacket(data);
  },
  [] (std::string const& data) {
    std::cout << "in packet 2" << std::endl;
    return new APacket(data);
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
  _buffer.resize(APacket::kMaxSize);
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
  _buffer.resize(APacket::kMaxSize);
  _handle = [this] (ISocket::returnCode ret, size_t sizeRec, std::string addr, int port) {
    std::cout << "Message received from : " << addr << ":" << port << " ==> " << _buffer << std::endl;
    _packHandlers[APacket::sGetType(_buffer)](_buffer);
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
      std::cerr << "Error while writing" << std::endl;
  });
}

APacket* Networker::getLastPacket()
{
  APacket* ret = _packList.back();

  _packList.pop_back();
  return ret;
}
