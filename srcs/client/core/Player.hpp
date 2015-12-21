#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <SFML/Graphics/Shader.hpp>
#include <string>
#include "Time.hpp"
#include "AUnit.hpp"

#include "Animation.hpp"

namespace Unit {

class Player : public AUnit {

public:
  Player(int x, int y, unsigned int id, Time::stamp creationTime, std::string name, float param);
  virtual ~Player();

public:

  std::string     getName() const;
  color           getColor() const;
  /*
  void		  getHit(AUnit *);
  */
  void		setX(int x);
  void		setY(int y);
  void		move(dir, Time::stamp);

  virtual void	  render(Time::stamp tick, sf::RenderWindow & window);
  virtual pos     move(Time::stamp tick) const;

private:
  color         _color;
  std::string   _name;
  int		_trueX;
  int		_trueY;

  int		_lastVerticalMove;
  Animation	_anim;
 };
}

#endif /* Player_hpp */
