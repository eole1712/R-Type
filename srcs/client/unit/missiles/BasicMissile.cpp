#include <algorithm>
#include <string>
#include "AMissile.hpp"
#include "BasicMissile.hpp"
#include "Game.hpp"
#include "Map.hpp"

extern "C"
{
  Unit::AUnit*	NewUnit(int x, int y, unsigned int id, Time::stamp creationTime)
  {
    return (new Unit::BasicMissile(x, y, id, creationTime));
  }

  void	DeleteMissile(Unit::AUnit* missile)
  {
    delete missile;
  }
}

namespace Unit
{

BasicMissile::BasicMissile(int x, int y, unsigned int id, Time::stamp creationTime)
  : AUnit(x, y, id, creationTime),
    _mySprite(std::string("../../resources/sprites/red ship2.fly.33x36x8.png"), 8)
{}

BasicMissile::~BasicMissile()
{}

Unit::pos            BasicMissile::move(Time::stamp tick) const
{
  Time::stamp diff = tick -_creationTime;
  pos p = std::make_pair(_x + diff / 10000, _y + diff / 10000);

  return p;
}

void		BasicMissile::render(Time::stamp tick, sf::RenderWindow & window)
{
  pos p = move(tick);

  _mySprite.setPosition(p.first, p.second);
  window.draw(_mySprite);
}

}
