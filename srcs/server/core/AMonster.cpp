#include "GameUtils.hpp"
#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "MissileFactory.hpp"

namespace Unit
{

  namespace Monster
  {

    AMonster::AMonster(unsigned int hp, int x, int y,
                       Unit::boxType hitBox, Missile::type weapon, unsigned int id, unsigned int gameID, Timer::time time)
      : AUnit(hp, Unit::ENEMY, x, y, hitBox, id, gameID, time), _weapon(weapon), _time(0)
    {}

    AMonster::~AMonster()
    {}

    Unit::type	AMonster::getType() const
    {
      return (Unit::MONSTER);
    }

      Missile::AMissile*          AMonster::shoot(Timer::time time)
    {
      if (!_time.isFinished())
        return NULL;

        Missile::AMissile *m = Missile::Factory::getInstance()->createMissile(_weapon, this, GameUtils::Game::getNewID(_gameID), GameUtils::Game::now(_gameID));

      _time.reset(m->getTime());

      return m;
    }
  }

}
