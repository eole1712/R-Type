#ifndef NETSERVER_H_
# define NETSERVER_H_

#include "Networker.hpp"

class NetServer : public Networker
{
public:
  NetServer(int port, NetManager*, IPacketHandler*);
  virtual ~NetServer();
  void sendAll(APacket*);
};

#endif /* !NETSERVER_H_ */
