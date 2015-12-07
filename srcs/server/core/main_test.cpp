#include "Game.hpp"

int	main()
{
  Game				game(0);

  game.getMonsterFactory()->addMonsterType(Unit::Monster::type::MONSTERTEST, "libs/MonsterTest.so");
  return (0);
}
