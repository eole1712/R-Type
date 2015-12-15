#ifndef GAME_H_
# define GAME_H_

# include <list>
# include <SFML/Graphics.hpp>
//# include "Thread.hpp"
//# include "Lock.hpp"
# include "Time.hpp" 
# include "Key.hpp"
# include "AUnit.hpp"
# include "Player.hpp"

class IMap;
class IScoreList;

class Game
{
public:
  Game(sf::RenderWindow & window, Unit::Player & player);
  virtual ~Game();

public:  
  Unit::Player*		getLocalPlayer();
  void			setFinish();
  bool			getFinish() const;
  void			connectUnit(Unit::AUnit &);
  void			disconnectUnit(unsigned int);
  Unit::AUnit &		operator[](unsigned int id);

private:
  //void			thread(Game * _this);
  void			loop();
  void			pollEvent();
  void			render();

  typedef std::map<unsigned int, Unit::AUnit *> RemoteMap;

private:
  sf::RenderWindow &		_window;
  //Thread<Game *>		_thread;
  Time::stamp			_tick;
  Unit::Player &		_localPlayer;
  RemoteMap			_map;
  bool				_finish;  
  Key::Bind<Game *>		_input;
  // std::list<Unit::Player *>	_player;
  
};

#endif /* !GAME_H_ */
