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
  Game(Client * client, sf::RenderWindow & window, Unit::Player & player);
  virtual ~Game();

public:  
  void			loop();
  Unit::Player *	getLocalPlayer();
  Unit::Player *	getPlayer(unsigned int id);
  void			setFinish();
  bool			getFinish() const;
  void			connectUnit(Unit::AUnit &);
  void			disconnectUnit(unsigned int);
  Unit::AUnit &		operator[](unsigned int id);

private:
  void			pollEvent();
  void			render();

  typedef std::map<unsigned int, Unit::AUnit *> RemoteMap;

private:
  Client *			_client;
  sf::RenderWindow &		_window;
  Time::stamp			_tick;
  Unit::Player &		_localPlayer;
  RemoteMap			_map;
  bool				_finish;
  Time::stamp			_creationTime;
  Key::Bind<Game *>		_input;  
};

#endif /* !GAME_H_ */
