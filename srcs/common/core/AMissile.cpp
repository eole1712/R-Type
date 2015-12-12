
#include "AMissile.hpp"
#include "AUnit.hpp"

namespace Unit {
  namespace Missile {
    
    AMissile::AMissile(unsigned int x, unsigned int y, boxType hitBox,
                       unsigned int dammage, AUnit *unit, dir d)
    : AUnit(1, unit->getTeam(), x, y, hitBox, d), _dammage(dammage), _origin(unit)
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