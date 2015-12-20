#include <iostream>
#include "MonsterTest.hpp"

extern "C"
{
  Unit::MonsterTest *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  {
    return (new Unit::MonsterTest(x, y, id, creationTime, param));
  }

  void					DeleteUnit(Unit::MonsterTest * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  MonsterTest::MonsterTest(int x, int y, unsigned int id, Time::stamp creationTime, float param)
    : AUnit(x, y, id, creationTime, param),
      _mySprite(std::string("../resources/sprites/red ship2.fly.33x36x8.png"), 8)
  {
    _mySprite.scale(2.5, 2.5);
  }
  
  MonsterTest::~MonsterTest()
  {}
  
  pos            MonsterTest::move(Time::stamp time) const
  {
      uintmax_t diff = time - _creationTime;
      pos p = std::make_pair(_x - (diff / 10000), _y);
      
      return p;
  }
  
  void	MonsterTest::render(Time::stamp tick, sf::RenderWindow & window)
  {
    pos p = move(tick);
    
    _mySprite.setPosition(p.first, p.second);
    window.draw(_mySprite.getFrame());
  }
}
