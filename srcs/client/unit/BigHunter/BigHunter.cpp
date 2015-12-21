#include <cmath>
#include <iostream>
#include "BigHunter.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport)   Unit::AUnit *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param);
#endif
  Unit::AUnit *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  {
    return (new Unit::BigHunter(x, y, id, creationTime, param));
  }

#if (defined _WIN32)
  __declspec(dllexport)   void		DeleteUnit(Unit::BigHunter * monster);
#endif
  void					DeleteUnit(Unit::BigHunter * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  BigHunter::BigHunter(int x, int y, unsigned int id, Time::stamp creationTime, float param)
    : AUnit(x, y, id, creationTime, param),
      _mySprite(std::string("../resources/sprites/red ship2.fly.33x36x8.png"), 8)
  {
    _mySprite.scale(1.8f, 1.8f);
  }
  
  BigHunter::~BigHunter()
  {}

  pos            BigHunter::move(Time::stamp tick) const
  {
    long diff = static_cast<long>(tick - _creationTime) / 10;
    
    pos p = std::make_pair(_x - diff, static_cast<int>(_y + std::sin((diff % 2600) / 100.0) * 100.0));
    return p;
  }
  
  void	BigHunter::render(Time::stamp tick, sf::RenderWindow & window)
  {
    pos p = move(tick);
    
    _mySprite.setPosition(static_cast<float>(p.first), static_cast<float>(p.second));
    window.draw(_mySprite.getFrame());
  }
}
