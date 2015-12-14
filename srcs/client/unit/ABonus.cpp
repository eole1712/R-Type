#include <utility>
#include "AUnit.hpp"
#include "ABonus.hpp"
#include "Timer.hpp"

namespace Unit
{

  namespace Bonus
  {

  ABonus::ABonus(int x, int y, unsigned int id, unsigned int gameID, Timer::time creationTime)
    : AUnit(Unit::ENEMY, x, y, id, gameID, creationTime)
    {}

    ABonus::~ABonus()
    {}

    Unit::type	ABonus::getType() const
    {
      return (Unit::MISSILE);
    }

  pos	ABonus::move() const
  {
    // todo
    return (std::make_pair(0, 0));
  }

  }

}
