#include "AMissile.hpp"
#include "AUnit.hpp"
#include "Timer.hpp"

namespace Unit {
  namespace Missile {

    AMissile::AMissile(team t, unsigned int x, unsigned int y, unsigned int id, unsigned int gameID,
		       Timer::time creationTime)
      : AUnit(t, x, y, id, gameID, creationTime)
    {
    }

    AMissile::~AMissile()
    {
    }

    Unit::type      AMissile::getType() const
    {
      return MISSILE;
    }
  }
}
