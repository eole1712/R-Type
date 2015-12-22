#ifndef NETWORKER_H_
#define NETWORKER_H_

//comment to enable pings
//#define NO_PING
//#define DEBUG_NETWORK


#include "APacket.hpp"
#include "ISocket.hpp"
#include "NetManager.hpp"
#include "IPacketHandler.hpp"
#include "Lock.hpp"
#include <mutex>
#include <functional>
#include <vector>
#include <list>

class Networker
{
protected:
  enum peerInd {
    addr = 0,
    port,
    time
  };
public:
  Networker(int port);
  Networker(int port, NetManager*, IPacketHandler*);
  virtual ~Networker();
  APacket* getLastPacket();
  void start();
  void answer(APacket* pack, int id);
  void send(APacket* pack, int id);
  void stopPing();
  void setTimeout(int id);
  void pingFunction(std::nullptr_t);
  static uint64_t getCurTime();
protected:
  Lock _lock;
  IPacketHandler* _PacketHandler;
  ISocket* _sock;
  std::map<int, std::tuple<std::string, int, uint64_t> > _peers;
  std::list<APacket*> _packList;
  ISocket::receiveHandler _handle;
  std::string _buffer;
  std::vector<std::function<void(APacket*, int)> > _packInterp;
  bool _finished;
  std::list<unsigned int> _toErase;
  static std::function<void(ISocket*, std::string&, ISocket::receiveHandler)> _asyncRec;
  static const std::vector<std::function<APacket*(std::string const&) > > _packHandlers;

};

#endif /* !NETWORKER_H_ */
