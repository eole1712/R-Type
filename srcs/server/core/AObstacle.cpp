#include "AUnit.hpp"
#include "AObstacle.hpp"

namespace Unit
{

namespace Obstacle
{

AObstacle::AObstacle(unsigned int x, unsigned int y, Unit::boxType hitBox)
  : AUnit(0, Unit::ENEMY, x, y, hitBox)
{}

AObstacle::~AObstacle()
{}

Unit::type	AObstacle::getType() const
{
  return (Unit::OBSTACLE);
}

}

}
