#include "UdpSocket.hpp"
#include <stdexcept>
#include <cstring>
#include <iostream>

// UdpSocket::UdpSocket()
//   : _port(0), _rcvSd(-1), _manager(NetManager::getInstance())
// {
//   #ifdef _WIN32
//   WSADATA WsaData;
//   if (WSAStartup(MAKEWORD(2, 2), &WsData) == false)
//     throw std::runtime_error("Winsock init failed");
//   #endif
// }

UdpSocket::UdpSocket(int port)
  : _port(port), _sd(-1), _manager(NetManager::getInstance())
{
  #ifdef _WIN32
  WSADATA WsaData;
  if (WSAStartup(MAKEWORD(2, 2), &WsData) == false)
    throw std::runtime_error("Winsock init failed");
  #endif
  _sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (_sd <= 0)
    throw std::runtime_error("failed to create socket");

  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(static_cast<unsigned short>(port));

  if (bind(_sd, reinterpret_cast<const sockaddr *>(&_addr), sizeof(sockaddr_in)) < 0)
    throw std::runtime_error("failed to bind socket");

  _manager->addSocket(_sd, this);
}

UdpSocket::UdpSocket(int rcvPort, std::string netAddr)
  : _port(rcvPort), _manager(NetManager::getInstance())
{
  #ifdef _WIN32
  WSADATA WsaData;
  if (WSAStartup(MAKEWORD(2, 2), &WsData) == false)
    throw std::runtime_error("Winsock init failed");
  #endif
  _sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (_sd <= 0)
    throw std::runtime_error("failed to create socket");

  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(static_cast<unsigned short>(_port));

  if (bind(_sd, reinterpret_cast<const sockaddr *>(&_addr), sizeof(sockaddr_in)) < 0)
    throw std::runtime_error("failed to bind socket");

  _addr.sin_addr.s_addr = inet_addr(netAddr.c_str());

  _manager->addSocket(_sd, this);
}

UdpSocket::UdpSocket(int rcvPort, std::string netAddr, NetManager* manager)
  : _port(rcvPort), _manager(manager)
{
  #ifdef _WIN32
  WSADATA WsaData;
  if (WSAStartup(MAKEWORD(2, 2), &WsData) == false)
    throw std::runtime_error("Winsock init failed");
  #endif
  _sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (_sd <= 0)
    throw std::runtime_error("failed to create socket");

  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(static_cast<unsigned short>(_port));

  if (bind(_sd, reinterpret_cast<const sockaddr *>(&_addr), sizeof(sockaddr_in)) < 0)
    throw std::runtime_error("failed to bind socket");

  _addr.sin_addr.s_addr = inet_addr(netAddr.c_str());

  _manager->addSocket(_sd, this);
}

UdpSocket::~UdpSocket()
{
  closeSocket();
  #ifdef _WIN32
  WSACleanup();
  #endif
}

bool UdpSocket::setNonBlocking()
{
  #ifdef _WIN32
  DWORD nonBlocking = 1;
  if (ioctlsocket(_sd, FIONBIO, &nonBlocking ) != 0)
      return false;
  #else
  int nonBlocking = 1;
  if (fcntl(_sd, F_SETFL, O_NONBLOCK, nonBlocking) == -1)
    return false;
  #endif
  return true;
}

void UdpSocket::closeSocket()
{
  if (_sd != -1)
    {
      #ifdef _WIN32
      closesocket(_sd);
      #else
      close(_sd);
      #endif
    }
}

bool UdpSocket::setPort(int port)
{
  closeSocket();
  _manager->deleteSocket(_sd);
  _sd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (_sd <= 0)
    return false;

  _manager->addSocket(_sd, this);

  in_addr_t save = _addr.sin_addr.s_addr;

  _addr.sin_family = AF_INET;
  _addr.sin_addr.s_addr = INADDR_ANY;
  _addr.sin_port = htons(static_cast<unsigned short>(port));

  if (bind(_sd, reinterpret_cast<const sockaddr *>(&_addr), sizeof(sockaddr_in)) < 0)
    return false;

  _addr.sin_addr.s_addr = save;
  return true;
}

void UdpSocket::setAddr(std::string netAddr)
{
  _addr.sin_addr.s_addr = inet_addr(netAddr.c_str());
}

void UdpSocket::setSendPort(int port)
{
  _addr.sin_port = htons(static_cast<unsigned short>(port));
}

size_t UdpSocket::send(std::string const& data)
{
  size_t res;

  res = sendto(_sd, data.c_str(), data.size(), 0, reinterpret_cast<sockaddr*>(&_addr), sizeof(sockaddr_in));

  return res;
}

void UdpSocket::async_send(std::string const& data, sendHandler callback)
{
  _manager->addSendCall(_sd, data, callback);

  //_sendQueue.push_back(std::make_pair(data, callback));
}

size_t UdpSocket::receive(std::string &data)
{
  #ifdef _WIN32
  typedef int socklen_t;
  #endif

  size_t ret;
  unsigned char cdata[bufferSize];
  unsigned int max_size = bufferSize;
  socklen_t fromAddrLen = sizeof(_lastAddr);

  if ((ret = recvfrom(_sd, cdata, max_size, 0, reinterpret_cast<sockaddr*>(&_lastAddr), &fromAddrLen)) <= 0)
    return ret;
  data.assign(reinterpret_cast<char*>(cdata), ret);
  return ret;
}

void UdpSocket::async_receive(std::string &buffer, receiveHandler callback)
{
  _manager->addReceiveCall(_sd, buffer, callback);
}

std::string UdpSocket::getLastPackAddr() const
{
  return std::string(inet_ntoa(_lastAddr.sin_addr));
}

int UdpSocket::getLastPackPort() const
{
  return ntohs(_lastAddr.sin_port);
}
