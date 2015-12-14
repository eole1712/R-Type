#include "Game.hpp"

int	main()
{
  Game				game(0);

    Monster::Factory::getInstance()->addMonsterType(Unit::Monster::type::MONSTERTEST, "libs/MonsterTest.so");
  return (0);
}
