#include "AUnit.hpp"
#include "ABonus.hpp"

namespace Unit
{

namespace Bonus
{

ABonus::ABonus(unsigned int x, unsigned int y, Unit::boxType hitBox, unsigned int id, unsigned int gameID)
  : AUnit(1, Unit::ENEMY, x, y, hitBox, UP, id, gameID)
{}

ABonus::~ABonus()
{}

Unit::type	ABonus::getType() const
{
  return (Unit::MISSILE);
}

}

}
