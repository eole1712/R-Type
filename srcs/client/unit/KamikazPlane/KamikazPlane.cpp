#include <cmath>
#include <iostream>
#include "KamikazPlane.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport)   Unit::AUnit *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param);
#endif
  Unit::AUnit *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  {
    return (new Unit::KamikazPlane(x, y, id, creationTime, param));
  }

#if (defined _WIN32)
  __declspec(dllexport)     void          DeleteUnit(Unit::AUnit * monster);
#endif
  void					DeleteUnit(Unit::AUnit * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  KamikazPlane::KamikazPlane(int x, int y, unsigned int id, Time::stamp creationTime, float param)
    : AUnit(x, y, id, creationTime, param),
      _mySprite(std::string("../resources/sprites/kamikaz plane.png"), 3)
  {
    _mySprite.scale(1.8f, 1.8f);
  }
  
  KamikazPlane::~KamikazPlane()
  {}

  pos            KamikazPlane::move(Time::stamp tick) const
  {
    long diff = static_cast<long>(tick - _creationTime) / 10;
    
    pos p = std::make_pair(_x - diff, _y);
    return p;
  }
  
  void	KamikazPlane::render(Time::stamp tick, sf::RenderWindow & window)
  {
    pos p = move(tick);
    
    _mySprite.setPosition(static_cast<float>(p.first), static_cast<float>(p.second));
    window.draw(_mySprite.getFrame());
  }

  typeID	KamikazPlane::getType() const
  {
    return KAMIKAZPLANE;
  }
}
