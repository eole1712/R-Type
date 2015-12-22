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
#include "ClientKeyboardPressPacket.hpp"

#include <iostream>
#include <algorithm>

#define DEBUG 0

std::function<void(ISocket*, std::string&, ISocket::receiveHandler)> Networker::_asyncRec = std::bind(&ISocket::async_receive, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

std::vector<std::function<APacket*(std::string const&) > > const Networker::_packHandlers = {
  [] (std::string const& data) {
    ServerConnexionPacket* pack = new ServerConnexionPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ServerGameInfoPacket* pack = new ServerGameInfoPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ServerGameConnectPacket* pack = new ServerGameConnectPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ServerPlayerMovePacket* pack = new ServerPlayerMovePacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ServerUnitSpawnPacket* pack = new ServerUnitSpawnPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ServerUnitDiePacket* pack = new ServerUnitDiePacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ServerTimerRefreshPacket* pack = new ServerTimerRefreshPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
    [] (std::string const& data) {
    ServerPingPacket* pack = new ServerPingPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ClientConnexionPacket* pack = new ClientConnexionPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ClientGameInfoPacket* pack = new ClientGameInfoPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ClientGameConnectPacket* pack = new ClientGameConnectPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  },
  [] (std::string const& data) {
    ClientKeyboardPressPacket* pack = new ClientKeyboardPressPacket(data);
    if (DEBUG) std::cout << *pack << std::endl;
    return pack;
  }
};

Networker::Networker(int port)
: _sock(new UdpSocket(port))
{

  _buffer.resize(APacket::kMaxPacketSize);
  _handle = [this] (ISocket::returnCode, ssize_t, std::string, int) {
    _packHandlers[APacket::sGetType(_buffer)](_buffer);
    _asyncRec(_sock, _buffer, _handle);
  };
  _asyncRec(_sock, _buffer, _handle);
}

Networker::Networker(int port, NetManager* manager, IPacketHandler* handler)
  : _sock(new UdpSocket(port, "", manager)), _finished(false)
{
  _PacketHandler = handler;
  _buffer.resize(APacket::kMaxPacketSize);
  _handle = [this] (ISocket::returnCode, ssize_t sizeRec, std::string addr, int port) {
    std::unique_lock<Lock> l(_lock);
    APacket* pack;
    bool found = false;
    unsigned int id = 0;

    if (sizeRec <= 0) {
      std::cerr << "receive error" << std::endl;
      return;
    }
    for (auto elem : _peers) {
            if (std::get<peerInd::port>(elem.second) == port &&
	  inet_addr(std::get<peerInd::addr>(elem.second).c_str()) == inet_addr(addr.c_str())) {
       found = true;
       id = elem.first;
       break;
     }
     ++id;
   }
   if (DEBUG) std::cout << "[RECEIVING FROM :"<< id <<"] ";
    pack = _packHandlers[APacket::sGetType(_buffer)](_buffer);
    if (!found) {
      std::cout << "New peer ! : " << addr << ":" << port << std::endl;
      _peers[id] = std::make_tuple(addr, port, getCurTime());
    }
  l.unlock();
  _PacketHandler->handlePacket(pack, id);
  delete pack;
  _asyncRec(_sock, _buffer, _handle);
};
_asyncRec(_sock, _buffer, _handle);
}

Networker::~Networker()
{

}

void Networker::send(APacket *pack, int id)
{

//REMOVE WHEN NO DEBUG
  if (DEBUG) {
  APacket* packdebug;
   std::cout << "[SENDING TO : "<< id <<"] ";
    packdebug = _packHandlers[APacket::sGetType(pack->getData())](pack->getData());
    delete packdebug;
  }
//!REMOVE WHEN NO DEBUG
    std::lock_guard<Lock> l(_lock);
    std::string data = pack->getData();
    unsigned long dataSize = data.size();

  if (_peers.size() <= unsigned(id))
    return;

  _sock->async_send(data, [dataSize] (ISocket::returnCode ret, size_t written) {
    if (written != dataSize || ret != ISocket::Sucess)
      std::cerr << "Error while writing ==> written : " << written << "expected : " << dataSize << " ret : " << ret << std::endl;
  }, std::get<peerInd::addr>(_peers[id]), std::get<peerInd::port>(_peers[id]));
}

// APacket* Networker::getLastPacket()
// {
//   if (_packList.empty())
//     return nullptr;

//   APacket* ret = _packList.back();

//   _packList.pop_back();
//   return ret;
// }

// void Networker::answer(APacket* pack, int id)
// {
//   ServerConnexionPacket* srvPack;

//   std::cout << "type : " << static_cast<int>(pack->getType()) << std::endl;
//   std::cout << "id : " << id << std::endl;
//   if (pack->getType() == 1) {
//     std::cout << "answering to : " << _peers[id].first << ":" << _peers[id].second << std::endl;
//     srvPack = new ServerConnexionPacket;
//     srvPack->setServerString("Coucou, bienvenue chez les poneys !");
//     srvPack->setStatus(true);
//     srvPack->setId(0);
//     send(srvPack, id);
//   }
// }

uint64_t Networker::getCurTime()
{
  return std::chrono::system_clock::now().time_since_epoch().count();
}

void Networker::setTimeout(int id)
{
  std::lock_guard<Lock> l(_lock);

  std::get<peerInd::time>(_peers[id]) = getCurTime();
}

void Networker::stopPing()
{
  _finished = true;
}

void Networker::pingFunction(std::nullptr_t)
{
  uint64_t diff;
  struct timeval t;

  while (!_finished) {
    std::unique_lock<Lock> l(_lock);

    t.tv_sec = 1;
    t.tv_usec = 0;
    for (auto& peer : _peers) {
      diff = getCurTime() - std::get<peerInd::time>(peer.second);
      if (diff > 1000000000) {
	std::cout << "Timeout !" << std::endl;
	ServerPingPacket pack;
	pack.setStatus(true);
	l.unlock();
	send(&pack, peer.first);
	l.lock();
      }
      if (diff > 5000000000) {
	std::cout << "MUST EXIT ! id : " << peer.first << std::endl;
	_toErase.push_back(peer.first);
      }
      std::cout << "différence : " << diff << std::endl;
    }
    for (auto& elem : _toErase)
      if (_peers.find(elem) != _peers.end()) {
	_peers.erase(elem);
	std::cout << "erasing elem : " <<  elem << std::endl;
	_PacketHandler->disconnectPlayer(elem);
      }
    _toErase.clear();
    l.unlock();
    select(0, NULL, NULL, NULL, &t);
  }
}
