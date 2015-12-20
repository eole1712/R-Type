#include <iostream>
#include <cmath>
#include "BasicMissile.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport) Unit::BasicMissile *		NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param);
#endif
  Unit::BasicMissile *		NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  {
    return (new Unit::BasicMissile(x, y, id, creationTime, param));
  }

#if (defined _WIN32)
  __declspec(dllexport)   void				DeleteUnit(Unit::BasicMissile * monster);
#endif
  void				DeleteUnit(Unit::BasicMissile * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  BasicMissile::BasicMissile(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  : AUnit(x, y, id, creationTime, param),
  _mySprite(std::string("../resources/sprites/red ship2.fly.33x36x8.png"), 8)
  {
    _mySprite.scale(2.5, 2.5);
  }

  BasicMissile::~BasicMissile()
  {}
  
  Unit::pos            BasicMissile::move(Time::stamp tick) const
  {
    long diff = static_cast<long>(tick - _creationTime) / 10;
    
    pos p = std::make_pair(_x + diff, _y + std::sin((diff % 2600) / 100.0) * 100.0);
    //  pos p = std::make_pair(_x, _y);
    return p;
  }
  
  void		BasicMissile::render(Time::stamp tick, sf::RenderWindow & window)
  {
    pos p = move(tick);
    
    _mySprite.setPosition(p.first, p.second);
    window.draw(_mySprite.getFrame());
  }
}
