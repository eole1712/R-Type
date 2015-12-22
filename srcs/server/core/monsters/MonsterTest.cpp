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
    : AMonster(1, x, y, std::make_pair(59, 65), Missile::WAVE, id, gameID, time)
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
        return nullptr;

      Missile::AMissile *m = Missile::Factory::getInstance()->createMissile(_weapon, this, 0, time);

      _time.reset(static_cast<uintmax_t>(m->getTime() * 1000));
      return m;
    }

      Unit::pos            MonsterTest::move(Timer::time time) const
    {
      int diff = static_cast<int>((time - _creationTime) / 10);

      pos p = std::make_pair(_x - diff, static_cast<int>(_y + std::sin((diff % 2600) / 100.0) * 100.0));
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
