#ifndef GAME_H_
# define GAME_H_

# include <list>
# include <SFML/Graphics.hpp>
# include "Client.hpp"
# include "Time.hpp" 
# include "Key.hpp"
# include "Player.hpp"

class Client;

class Game
{
public:
    Game(IGameHandler * client, sf::RenderWindow & window, int playerId, std::string);
  virtual ~Game();

public:  
  static void		sendKey(Game * param, Key::keyState & key,
				sf::Keyboard::Key keycode, Key::event e);
  void			loop();
  Unit::Player *	getLocalPlayer();
  Unit::Player *	getPlayer(unsigned int id);
  void			setFinish();
  void			setTimer(unsigned long time);
  bool			getFinish() const;
  void			connectUnit(Unit::typeID type, int x, int y, unsigned int id,
				    Time::stamp creationTime, int param);
  void			disconnectUnit(unsigned int);
  Unit::AUnit &		operator[](unsigned int id);

private:
  void			pollEvent();
  void			render();

  typedef std::map<unsigned int, Unit::AUnit *> RemoteMap;

private:
  IGameHandler *		_client;
  sf::RenderWindow &		_window;
  Time::stamp			_tick;
  std::string			_localPlayerName;
  int				_localPlayer;
  RemoteMap			_map;
  bool				_finish;
  Time::stamp			_creationTime;
  Key::Bind<Game *>		_input;  
};

#endif /* !GAME_H_ */
