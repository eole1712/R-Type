#ifndef CLIENT_H_
# define CLIENT_H_

#include "NetClient.hpp"
#include "IPacketHandler.hpp"

class Client : public IPacketHandler
{
public:
  Client(int port = 6524);
  virtual ~Client();

  void handlePacket(APacket*, unsigned int id);
  void start();

protected:
  NetManager* _netManager;
  NetClient*  _netClient;

  std::vector<std::function<void(APacket*, unsigned int)> > _packetHandlerFuncs;
};

#endif /* !CLIENT_H_ */