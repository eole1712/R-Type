#include <utility>
#include "MonsterTest.hpp"

extern "C"
{
  Unit::Monster::AMonster*	NewMonster(int x, int y, unsigned int id, Time::stamp creationTime)
  {
    return (new Unit::Monster::MonsterTest(x, y, id, creationTime));
  }

  void	DeleteMonster(Unit::Monster::AMonster* monster)
  {
    delete monster;
  }
}

namespace Unit
{

  namespace Monster
  {

    MonsterTest::MonsterTest(int x, int y, unsigned int id, Time::stamp creationTime)
    : AMonster(x, y, id, creationTime)
    {}

    MonsterTest::~MonsterTest()
    {}

    Unit::pos            MonsterTest::move(Time::stamp tick) const
    {
      Time::stamp diff = tick -_creationTime;
      pos p = std::make_pair(_x + diff / 10000, _y + diff / 10000);
      
      return p;
    }

    void		MonsterTest::render(Time::stamp tick, sf::RenderWindow & window)
    {
      pos p = move(tick);

    }
  }

}
