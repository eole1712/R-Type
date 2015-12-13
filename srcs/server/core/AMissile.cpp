
#include "AMissile.hpp"
#include "AUnit.hpp"

namespace Unit {
  namespace Missile {
    
    AMissile::AMissile(boxType hitBox, unsigned int dammage, AUnit *unit, unsigned int id)
    : AUnit(1, unit->getTeam(), unit->getX(), unit->getY(), hitBox, id, unit->getGameID()), _dammage(dammage), _origin(unit)
    {
    }
    
    AMissile::~AMissile()
    {
    }
    
    unsigned int    AMissile::getDammage() const
    {
      return _dammage;
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