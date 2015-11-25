#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"

namespace Monster
{

AMonster::AMonster(unsigned int hp, unsigned int x, unsigned int y,
		   AUnit::boxType hitBox, Missile::type weapon)
  : AUnit(hp, AUnit::ENNEMY, x, y, hitBox), _weapon(weapon)
{}

AMonster::~AMonster()
{}

Unit::type	getType() const
{
  return (Unit::MONSTER);
}

}
