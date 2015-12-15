#include "Game.hpp"

int	main()
{
  Game				game(0, "Main");

    Monster::Factory::getInstance()->addMonsterType(Unit::Monster::type::MONSTERTEST, "libs/MonsterTest.so");
  return (0);
}
