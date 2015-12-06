#include "Game.hpp"
#include "MissileFactory.hpp"

int	main()
{
  Game				game(0);
  Unit::Missile::Factory*	missileFactory = Unit::Missile::Factory::getInstance();

  (void)missileFactory;
  return (0);
}
