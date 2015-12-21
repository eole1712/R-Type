
#include <iostream>
#include <algorithm>
#include "Player.hpp"

namespace Unit {

  Player::Player(int x, int y, unsigned int id, Time::stamp creationTime, std::string name, float param)
    : AUnit(x, y, id, creationTime, param),
      _color(static_cast<Unit::color>(id % 5)), _name(name),
      _trueX(x), _trueY(y),
      _lastVerticalMove(0), _anim(std::string("../resources/sprites/ship.colors.340x47x4.png"), 4)
  {
    _anim.pause();
    _anim.setFrameIndex(id % 5 - 1);
  }

  Player::~Player()
  {
  }

  std::string		Player::getName() const
  {
    return _name;
  }

  color			Player::getColor() const
  {
    return _color;
  }

  /*
  unsigned int		Player::getScore() const
  {
    return _score;
  }

  void			Player::incScore(unsigned int score)
  {
    _score += score;
  }
  void			Player::renderUI(sf::RenderWindow & window)
  {
  }
  */

  pos			Player::move(Time::stamp) const
  {
    return pos(_trueX, _trueY);
  }

void Player::setX(int x)
{
  _trueX = x;
}


void Player::setY(int y)
{
  _trueY = y;
}
    
  void			Player::render(Time::stamp , sf::RenderWindow & window)
  {
    _anim.setPosition(static_cast<float>(_trueX), static_cast<float>(_trueY));
    window.draw(_anim.getFrame());
    _lastVerticalMove = 0;
  }

  typeID		Player::getType() const
  {
    return PLAYERTYPE;
  }
}
