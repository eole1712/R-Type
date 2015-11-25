#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"

namespace Unit
{
  
  namespace Monster
  {
    
    AMonster::AMonster(unsigned int hp, unsigned int x, unsigned int y,
                       Unit::boxType hitBox, Missile::type weapon)
    : AUnit(hp, Unit::ENNEMY, x, y, hitBox), _weapon(weapon)
    {}
    
    AMonster::~AMonster()
    {}
    
    Unit::type	AMonster::getType() const
    {
      return (Unit::MONSTER);
    }
  }
  
}