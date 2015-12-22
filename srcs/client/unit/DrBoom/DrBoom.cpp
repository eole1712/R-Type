#include <cmath>
#include <iostream>
#include "DrBoom.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport)   Unit::AUnit *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param);
#endif
  Unit::AUnit *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  {
    return (new Unit::DrBoom(x, y, id, creationTime, param));
  }

#if (defined _WIN32)
  __declspec(dllexport)   void		DeleteUnit(Unit::BigHunter * monster);
#endif
  void					DeleteUnit(Unit::DrBoom * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  DrBoom::DrBoom(int x, int y, unsigned int id, Time::stamp creationTime, float param)
    : AUnit(x, y, id, creationTime, param),
      _mySprite(std::string("green jumper.jump.56x54x3..png"), 8)
  {
    _mySprite.scale(1.4f, 1.4f);
  }
  
  DrBoom::~DrBoom()
  {}

  pos            DrBoom::move(Time::stamp tick) const
  {
    long diff = static_cast<long>(tick - _creationTime) / 10;
    
    pos p = std::make_pair(_x - diff, _y);
    return p;
  }
  
  void	DrBoom::render(Time::stamp tick, sf::RenderWindow & window)
  {
    pos p = move(tick);
    
    _mySprite.setPosition(static_cast<float>(p.first), static_cast<float>(p.second));
    window.draw(_mySprite.getFrame());
  }
    
    Unit::typeID    DrBoom::getType() const
    {
        return DRBOOM;
    }
}
