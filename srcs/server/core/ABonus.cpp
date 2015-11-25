#include "AUnit.hpp"
#include "ABonus.hpp"

namespace Unit
{

namespace Bonus
{

ABonus::ABonus(unsigned int x, unsigned int y, Unit::boxType hitBox)
  : AUnit(1, Unit::ENNEMY, x, y, hitBox)
{}

ABonus::~ABonus()
{}

Unit::type	ABonus::getType() const
{
  return (Unit::MISSILE);
}

}

}
