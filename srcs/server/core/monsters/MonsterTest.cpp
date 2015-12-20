#include <cmath>
#include <utility>
#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "MonsterTest.hpp"
#include "MissileFactory.hpp"
#include "Timer.hpp"
#include "GameUtils.hpp"

// ébauche de classe pour test

extern "C"
{
#if (defined _WIN32)
  __declspec(dllexport)        Unit::Monster::AMonster* NewMonster(int x, int y, unsigned int id, unsigned int gameID, Timer::time time);
#endif
    Unit::Monster::AMonster*  NewMonster(int x, int y, unsigned int id, unsigned int gameID, Timer::time time)
  {
    return (new Unit::Monster::MonsterTest(x, y, id, gameID, time));
  }
  
#if (defined _WIN32)
  __declspec(dllexport)     void  DeleteMonster(Unit::Monster::AMonster* monster);
#endif
  void	DeleteMonster(Unit::Monster::AMonster* monster)
  {
    delete monster;
  }
}

namespace Unit
{

  namespace Monster
  {

      MonsterTest::MonsterTest(int x, int y, unsigned int id, unsigned int gameID, Timer::time time)
    : AMonster(1, x, y, std::make_pair((33 * 1.8), (36 * 1.8)), Missile::BASIC, id, gameID, time)
    {}

    MonsterTest::~MonsterTest()
    {}

    Monster::type	MonsterTest::getMonsterType() const
    {
      return (Monster::MONSTERTEST);
    }

      Missile::AMissile*	MonsterTest::shoot(Timer::time time)
    {
      if (!_time.isFinished())
        return NULL;

      Missile::AMissile *m = Missile::Factory::getInstance()->createMissile(_weapon, this, 0, time);

      _time.reset(m->getTime() * 1000);
      return m;
    }

      Unit::pos            MonsterTest::move(Timer::time time) const
    {
      uintmax_t diff = time - _creationTime;

      pos p = std::make_pair(_x - diff, _y + std::sin((diff % 2600) / 100.0) * 100.0);
      return p;
    }

    void	MonsterTest::getHit(AUnit*)
    {
      if (this->_hp > 0)
        this->_hp -= 1;
    }

    Unit::typeID  MonsterTest::getTypeID() const
    {
      return Unit::MONSTERTEST;
    }

  }

}
