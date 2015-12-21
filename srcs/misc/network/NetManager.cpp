#ifdef _WIN32
#include "Winsock2.h"
#else
#include <sys/select.h>
#endif
#include <stdexcept>

#include "NetManager.hpp"

#include <iostream>

NetManager* NetManager::_ptr = nullptr;

NetManager::NetManager()
  :_ret(ISocket::Sucess), _timeout(0), _finish(false)
{

}

NetManager::~NetManager()
{

}

NetManager* NetManager::getInstance()
{
  if (!_ptr)
    _ptr = new NetManager;
  if (!_ptr)
    throw std::runtime_error("Failed to allocate NetManager Singleton");
  return _ptr;
}

void NetManager::loopStart()
{
  getInstance()->loop();
}

void NetManager::addSendCall(int sd, std::string msg, ISocket::sendHandler& handler, std::string addr, int port)
{
  std::lock_guard<Mutex> locker(_mutex);

  _sendings[sd].push_front(std::make_tuple(msg, handler, addr, port));
}

void NetManager::addReceiveCall(int sd, std::string &buffer, ISocket::receiveHandler &handler)
{
  std::lock_guard<Mutex> locker(_mutex);
  _reiceivings[sd].push_front(std::make_pair(std::reference_wrapper<std::string>(buffer), handler));
}

void NetManager::addSocket(int sd, ISocket * sock)
{
  std::lock_guard<Mutex> locker(_mutex);

  if (_sockets.find(sd) == _sockets.end())
    _sockets[sd] = sock;
  std::cout << "socket added to manager" << std::endl;
}

bool NetManager::find(int sd)
{
  std::lock_guard<Mutex> locker(_mutex);

  return _sockets.find(sd) != _sockets.end();
}

void NetManager::deleteSocket(int sd)
{
  std::lock_guard<Mutex> locker(_mutex);

  if (_sockets.find(sd) != _sockets.end()) {
    _sockets.erase(sd);
    _sendings.erase(sd);
    _reiceivings.erase(sd);
  }
}

template <>
void NetManager::setFds<NetManager::sendList>(int& maxFd, fd_set& set)
{
  std::lock_guard<Mutex> locker(_mutex);

  for (auto& elem : _sendings)
  {
    if (!elem.second.empty())
    {
     FD_SET(elem.first, &set);
     if (elem.first > maxFd)
       maxFd = elem.first;
   }
 };
}

template <>
void NetManager::setFds<NetManager::receiveList>(int& maxFd, fd_set& set)
{
  std::lock_guard<Mutex> locker(_mutex);

  for (auto& elem : _reiceivings)
  {
    if (!elem.second.empty())
    {
     FD_SET(elem.first, &set);
     if (elem.first > maxFd)
       maxFd = elem.first;
   }
 };
}

template <>
void NetManager::doAction<NetManager::sendList>(fd_set& set, unsigned int)
{
  size_t ret = 0;
  std::unique_lock<Mutex> locker(_mutex);

  for (auto& elem : _sendings)
  {
    if (_sockets.find(elem.first) != _sockets.end()) {

     if (FD_ISSET(elem.first, &set) && !elem.second.empty()) {
       _sockets[elem.first]->setAddr(std::get<2>(elem.second.back()));
       _sockets[elem.first]->setSendPort(std::get<3>(elem.second.back()));
       ret = _sockets[elem.first]->send(std::get<0>(elem.second.back()));
	  //locker.unlock();
       std::get<1>(elem.second.back())(_ret, ret);
	  //locker.lock();
       elem.second.pop_back();
     }
   }
   else
   {
     _sockets[elem.first]->setAddr(std::get<2>(elem.second.back()));
     _sockets[elem.first]->setSendPort(std::get<3>(elem.second.back()));
	  //locker.unlock();
     std::get<1>(elem.second.back())(ISocket::UndefFD, ret);
	  //locker.lock();
     _sockets.erase(elem.first);
   }
 }
}

template <>
void NetManager::doAction<NetManager::receiveList>(fd_set& set, unsigned int)
{
  size_t ret = 0;
  std::unique_lock<Mutex> locker(_mutex);

  for (auto& elem : _reiceivings)
  {
    if (_sockets.find(elem.first) != _sockets.end()) {
     if (FD_ISSET(elem.first, &set) && !elem.second.empty()) {
       ret = _sockets[elem.first]->receive(elem.second.back().first);
       locker.unlock();
       elem.second.back().second(_ret, ret, _sockets[elem.first]->getLastPackAddr(), _sockets[elem.first]->getLastPackPort());
       locker.lock();
       elem.second.pop_back();
     }
   }
   else
   {
     elem.second.back().second(ISocket::UndefFD, ret, "", -1);
     elem.second.pop_back();
     _sockets.erase(elem.first);
   }
 }
}

void NetManager::stop()
{
  _finish = true;
}

void NetManager::loop()
{
  int maxFd = 0;
  fd_set readFds;
  fd_set writeFds;
  struct timeval tVal;

  //int timeout = 0;

  while (_ret == ISocket::Sucess && !_finish) {

    tVal.tv_sec = 0;
    tVal.tv_usec = 10000 + _timeout;

    FD_ZERO(&readFds);
    FD_ZERO(&writeFds);

    setFds<sendList>(maxFd, writeFds);
    setFds<receiveList>(maxFd, readFds);
    if (select(maxFd + 1, &readFds, &writeFds, NULL, &tVal) < 0)
      #ifdef _WIN32
      if (WSAGetLastError() == WSAENOTSOCK)
       _ret = ISocket::Fail;
#else
#if (defined __APPLE__)
     if (errno != EBADF)
#else
      if (errno != EBADFD)
#endif
       _ret = ISocket::Fail;
      #endif
     doAction<sendList>(writeFds, 0);
     doAction<receiveList>(readFds, 0);
   }
 }
