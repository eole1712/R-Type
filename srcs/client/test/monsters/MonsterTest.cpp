#include <utility>
#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "MonsterTest.hpp"
#include "MissileFactory.hpp"
#include "Timer.hpp"
#include "Game.hpp"

// ébauche de classe pour test

extern "C"
{
  Unit::Monster::AMonster*	NewMonster(int x, int y, unsigned int id, Timer::time creationTime)
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

    MonsterTest::MonsterTest(int x, int y, unsigned int id, Time::time creationTime)
    : AMonster(x, y, id, creationTime)
    {}

    MonsterTest::~MonsterTest()
    {}

    Monster::type	MonsterTest::getMonsterType() const
    {
      return (Monster::MONSTERTEST);
    }

    Unit::pos            MonsterTest::move() const
    {
      uintmax_t diff = Game::now(_gameID) - _creationTime;
      pos p = std::make_pair(_x + diff / 10000, _y + diff / 10000);

      return p;
    }

  }

}
