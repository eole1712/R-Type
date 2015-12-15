#include "AMonster.hpp"

namespace Unit
{

  namespace Monster
  {

  AMonster::AMonster(int x, int y, unsigned int id, unsigned int gameID, Time::stamp creationTime)
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
