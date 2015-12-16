#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <SFML/Graphics/Shader.hpp>
#include <string>
#include "Time.hpp"
#include "AUnit.hpp"

#include "Animation.hpp"

namespace Missile {

enum	type {
  BASIC
};

}

namespace Unit {

class Player : public AUnit {

public:
  Player(int x, int y, unsigned int id, Time::stamp creationTime, std::string name);
  virtual ~Player();

public:
  std::string     getName() const;
  color           getColor() const;

  /*
  void		  getHit(AUnit *);
  Missile::type   getWeapon() const;
  void            setWeapon(Missile::type);
  */

  void            move(dir, Time::stamp);

  //void		  renderUI(sf::RenderWindow & window);
  virtual void	  render(Time::stamp tick, sf::RenderWindow & window);
  virtual pos     move(Time::stamp tick) const;

private:
  color         _color;
  std::string   _name;
  bool		_shooting;
  Time::stamp	_shootTime;
  Missile::type _weapon;
  int		_trueX;
  int		_trueY;

  int		_lastVerticalMove;
  Animation	_anim;
  sf::Shader	_colorShader;
 };
}

#endif /* Player_hpp */
