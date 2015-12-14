#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "Timer.hpp"

namespace Unit
{

  namespace Monster
  {

  AMonster::AMonster(int x, int y, unsigned int id, unsigned int gameID, Timer::time creationTime)
    : AUnit(Unit::ENEMY, x, y, id, gameID, creationTime)
    {}

    AMonster::~AMonster()
    {}

    Unit::type	AMonster::getType() const
    {
      return (Unit::MONSTER);
    }
  }

}
