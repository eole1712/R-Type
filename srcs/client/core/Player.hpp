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
  Player(color, std::string name, unsigned int id);
  virtual ~Player();
  
public:
  std::string     getName() const;
  color           getColor() const;

  bool            isShooting() const;
  void		  shootSend();
  void		  shootLoad();

  Missile::type   getWeapon() const;
  void            setWeapon(Missile::type);

  unsigned int    getScore() const;
  void            incScore(unsigned int);

  void            move(dir, Time::stamp);
  virtual void	  render(sf::RenderWindow & window);

  //void		  renderUI(sf::RenderWindow & window);  
  virtual void    getHit(AUnit*);
  virtual type    getType() const;
  virtual pos     move() const;
    
private:
  color           _color;
  std::string     _name;
  bool		  _shooting;
  Time::stamp	  _shootTime;	
  Missile::type   _weapon;
  unsigned int    _score;

  int		  _lastVerticalMove;
  Animation	  _anim;
  sf::Shader	  _colorShader;
 };
}

#endif /* Player_hpp */
