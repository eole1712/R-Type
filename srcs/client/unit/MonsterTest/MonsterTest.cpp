#include <iostream>
#include "MonsterTest.hpp"

extern "C"
{
  Unit::MonsterTest *			NewUnit(int x, int y, unsigned int id, Time::stamp creationTime)
  {
    return (new Unit::MonsterTest(x, y, id, creationTime));
  }

  void					DeleteUnit(Unit::MonsterTest * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  MonsterTest::MonsterTest(int x, int y, unsigned int id, Time::stamp creationTime)
    : AUnit(x, y, id, creationTime),
      _mySprite(std::string("../../resources/sprites/red ship2.fly.33x36x8.png"), 8)
  {
    _mySprite.scale(2.5, 2.5);
  }
  
  MonsterTest::~MonsterTest()
  {}
  
  pos            MonsterTest::move(Time::stamp tick) const
  {
    long diff = static_cast<long>(tick - _creationTime) / 10;
    
    pos p = std::make_pair(_x + diff, _y + diff % 50);
    return p;
  }
  
  void	MonsterTest::render(Time::stamp tick, sf::RenderWindow & window)
  {
    pos p = move(tick);
    
    _mySprite.setPosition(p.first, p.second);
    window.draw(_mySprite.getFrame());
  }
}