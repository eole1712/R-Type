#ifndef CLIENT_H_
# define CLIENT_H_

#include "ClientKeyboardPressPacket.hpp"
#include "NetClient.hpp"
#include "IPacketHandler.hpp"
#include "Menu.hpp"
#include "Game.hpp"
#include "IGameHandler.hpp"
#include "IMenuHandler.hpp"
#include "Lock.hpp"

#include <vector>
#include <tuple>

class Game;
class Menu;

class Client : public IPacketHandler, IGameHandler, IMenuHandler
{
public:
  typedef std::tuple<Unit::typeID, int, int, unsigned int,
		     Time::stamp, float>		unitObject;
  Client(int port = 6524);
  virtual ~Client();
  void handlePacket(APacket*, unsigned int id);
  void selectGame(std::string const& name, int id);
  void connect(std::string const& ip, std::string const& name);
  void refreshGames();
  void setGame(Game*);
  void createGame(std::string const& name);
  void sendKey(ClientKeyboardPressPacket::keyEvent);
  void start();
  void disconnectPlayer(unsigned int id);
  uint32_t getRoomConnected();
  virtual IGameHandler* getGameHandler();
protected:
  NetManager* _nm;
  NetClient*  _nc;
  std::vector<unitObject> _toCreate;
  std::vector<std::function<void(APacket*, unsigned int)> > _packetHandlerFuncs;
  //std::list<Unit::AUnit*> _units;
  uint32_t _connected;
  Menu* _menu;
  int _playerId;
  Game* _game;
  Lock _lock;
};

#endif /* !CLIENT_H_ */
