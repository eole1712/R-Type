#ifndef GAME_H_
# define GAME_H_

# include <list>
# include <SFML/Graphics.hpp>
# include <tuple>
# include "Client.hpp"
# include "Time.hpp" 
# include "Key.hpp"
# include "Player.hpp"

class Client;

class Game
{
public:
    Game(IGameHandler * client, sf::RenderWindow & window, int playerId, std::string, unsigned long time);
  virtual ~Game();


public:  
  typedef std::tuple<Unit::typeID, int, int, unsigned int,
		     Time::stamp, std::string, float>		unitObject;

  static void		sendKey(Game * param, Key::keyState & key,
				sf::Keyboard::Key keycode, Key::event e);
  void			loop();
  Unit::Player *	getLocalPlayer();
  Unit::Player *	getPlayer(unsigned int id);
  void			setFinish();
  void			setTimer(unsigned long time);
  Time::stamp   getTimer();
  bool			getFinish() const;
  void			createUnit();
  void			deleteUnit();
  void			connectUnit(Unit::typeID type, int x, int y, unsigned int id,
				    Time::stamp creationTime, int param);
  void			disconnectUnit(unsigned int);
  Unit::AUnit*		operator[](unsigned int id);

private:
  void			pollEvent();
  void			render();

  typedef std::map<unsigned int, Unit::AUnit *> RemoteMap;

private:
  
  IGameHandler *		_client;
  sf::RenderWindow &		_window;
  Time::stamp			_tick;
  std::list<unitObject>		_createStack;
  std::list<Unit::AUnit*>	_deleteStack;
  std::string			_localPlayerName;
  unsigned int			_localPlayer;
  RemoteMap			_map;
  bool				_finish;
  Time::stamp			_creationTime;
  Key::Bind<Game *>		_input;
  Lock				_lock;
  //Lock				_lockMap;
  Animation			_background;
  SoundPlayer			_soundPlayer;
};

#endif /* !GAME_H_ */
