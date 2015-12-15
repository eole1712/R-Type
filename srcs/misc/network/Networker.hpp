#ifndef NETWORKER_H_
#define NETWORKER_H_

#include "APacket.hpp"
#include "ISocket.hpp"
#include "NetManager.hpp"
#include "IPacketHandler.hpp"
#include <functional>
#include <vector>
#include <list>

class Networker
{
public:
  Networker(int port);
  Networker(int port, NetManager*, IPacketHandler*);
  virtual ~Networker();
  APacket* getLastPacket();
  void start();
  void answer(APacket* pack, int id);
protected:
  void send(APacket*, int id);
protected:
  IPacketHandler* _PacketHandler;
  ISocket* _sock;
  std::vector<std::pair<std::string, int> > _peers;
  std::list<APacket*> _packList;
  ISocket::receiveHandler _handle;
  std::string _buffer;
  std::vector<std::function<void(APacket*, int)> > _packInterp;
  static std::function<void(ISocket*, std::string&, ISocket::receiveHandler)> _asyncRec;
  static const std::vector<std::function<APacket*(std::string const&) > > _packHandlers;
};

#endif /* !NETWORKER_H_ */
