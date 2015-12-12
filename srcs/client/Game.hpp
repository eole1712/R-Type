#ifndef GAME_H_
# define GAME_H_

# include <list>
# include <SFML/Graphics.hpp>
# include "Time.hpp" 
# include "KeyBind.hpp"
# include "AUnit.hpp"
# include "Player.hpp"

class IMap;
class IScoreList;

class Game
{
public:
  Game(std::string host, Unit::color color, std::string name);
  virtual ~Game();

public:  
  Unit::Player*		getLocalPlayer();

  void			connectUnit(Unit::AUnit &);
  void			disconnectUnit(unsigned int);

  void			pollEvent(sf::RenderWindow &, Time::stamp);
  void			render(sf::RenderWindow &);

  typedef std::map<unsigned int, Unit::AUnit *> RemoteMap;

private:
  const std::string		_host;
  Unit::Player			_localPlayer;
  RemoteMap			_map;
  
  Key::Bind<Game *>		_input;
  // std::list<Unit::Player *>	_player;
};

#endif /* !GAME_H_ */
