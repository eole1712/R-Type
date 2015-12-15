#ifndef CLIENT_H_
# define CLIENT_H_

#include "NetClient.hpp"
#include "IPacketHandler.hpp"
#include "Menu.hpp"
#include "Game.hpp"

class Menu;

class Client : public IPacketHandler
{
public:
  Client(int port = 6524);
  virtual ~Client();
  void handlePacket(APacket*, unsigned int id);
  void selectGame(std::string const& name);
  void connect(std::string const& ip, std::string const& name);
  void setGame(Game*);
  void sendKey();
  void start();
protected:
  NetManager* _nm;
  NetClient*  _nc;
  std::vector<std::function<void(APacket*, unsigned int)> > _packetHandlerFuncs;
  std::map<std::string, uint32_t> _rooms;
  Menu* _menu;
  int _playerId;
  Game* _game;
};

#endif /* !CLIENT_H_ */
