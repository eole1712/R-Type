#ifndef PLAYER_HPP
# define PLAYER_HPP

#include <SFML/Graphics/Shader.hpp>
#include <string>
#include "Time.hpp"
#include "AUnit.hpp"
#include "AMissile.hpp"

#include "Animation.hpp"

namespace Unit {

class Player : public AUnit {

public:
  Player(int x, int y, unsigned int id, Time::stamp creationTime, std::string name);
  virtual ~Player();
  
public:
  std::string     getName() const;
  color           getColor() const;

  /*
  Missile::type   getWeapon() const;
  void            setWeapon(Missile::type);
  */

  void            move(dir, Time::stamp);
  virtual void	  render(sf::RenderWindow & window);

  //void		  renderUI(sf::RenderWindow & window);  
  virtual void    getHit(AUnit*);
  virtual pos     move() const;
    
private:
  color           _color;
  std::string     _name;
  bool		  _shooting;
  Time::stamp	  _shootTime;	
  Missile::type   _weapon;

  int		  _lastVerticalMove;
  Animation	  _anim;
  sf::Shader	  _colorShader;
 };
}

#endif /* Player_hpp */
