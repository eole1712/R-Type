#ifndef CLIENT_H_
# define CLIENT_H_

#include "NetClient.hpp"
#include "IPacketHandler.hpp"
#include "Menu.hpp"

class Client : public IPacketHandler
{
public:
  Client(int port = 6524);
  virtual ~Client();
  void handlePacket(APacket*, unsigned int id);
  void selectGame(std::string const& name);
  void start();
protected:
  NetManager* _nm;
  NetClient*  _nc;
  std::vector<std::function<void(APacket*, unsigned int)> > _packetHandlerFuncs;
  Menu* _menu;
  int _playerId;
};

#endif /* !CLIENT_H_ */
