#include "AMissile.hpp"
#include "AUnit.hpp"

namespace Unit {
  namespace Missile {

      AMissile::AMissile(boxType hitBox, unsigned int damage, AUnit *unit, unsigned int id, Timer::time time)
    : AUnit(1, unit->getTeam(), unit->getX(), unit->getY(), hitBox, id, unit->getGameID(), time), _damage(damage), _origin(unit)
    {
    }

    AMissile::~AMissile()
    {
    }

    unsigned int    AMissile::getDamage() const
    {
      return _damage;
    }

    AUnit*          AMissile::getOrigin() const
    {
      return _origin;
    }

    Unit::type      AMissile::getType() const
    {
      return MISSILE;
    }
  }
}
