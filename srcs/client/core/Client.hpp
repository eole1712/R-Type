#ifndef CLIENT_H_
# define CLIENT_H_

#include "NetClient.hpp"
#include "IPacketHandler.hpp"

class Client : public IPacketHandler
{
public:
  Client(int port);
  virtual ~Client();
  void handlePacket(APacket*, unsigned int id);

protected:
  NetManager* _nm;
  NetClient*  _nc;
  std::vector<std::function<void(APacket*, unsigned int)> > _packetHandlerFuncs;

};

#endif /* !CLIENT_H_ */
