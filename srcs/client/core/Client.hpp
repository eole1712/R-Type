#ifndef CLIENT_H_
# define CLIENT_H_

#include "ClientKeyboardPressPacket.hpp"
#include "NetClient.hpp"
#include "IPacketHandler.hpp"
#include "Menu.hpp"
#include "Game.hpp"

class Game;
class Menu;

class Client : public IPacketHandler
{
public:
  Client(int port = 6524);
  virtual ~Client();
  void handlePacket(APacket*, unsigned int id);
  void selectGame(std::string const& name);
  void connect(std::string const& ip, std::string const& name);
  void refreshGames();
  void setGame(Game*);
  void createGame(std::string const& name);
  void sendKey(ClientKeyboardPressPacket::keyEvent);
  void start();
protected:
  NetManager* _nm;
  NetClient*  _nc;
  std::vector<std::function<void(APacket*, unsigned int)> > _packetHandlerFuncs;
  //std::list<Unit::AUnit*> _units;
  std::map<std::string, uint32_t> _rooms;
  Menu* _menu;
  int _playerId;
  Game* _game;

};

#endif /* !CLIENT_H_ */
