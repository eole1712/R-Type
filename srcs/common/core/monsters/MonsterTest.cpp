#include <utility>
#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "MonsterTest.hpp"

// ébauche de classe pour test

extern "C"
{
  Unit::Monster::AMonster*	NewMonster(unsigned int x, unsigned int y)
  {
    return (new Unit::Monster::MonsterTest(x, y));
  }

  void	DeleteMonster(Unit::Monster::AMonster* monster)
  {
    delete monster;
  }
}

namespace Unit
{

namespace Monster
{

MonsterTest::MonsterTest(unsigned int x, unsigned int y)
  : AMonster(1, x, y, std::make_pair(5, 5), Missile::BASIC, LEFT)
{}

MonsterTest::~MonsterTest()
{}

Monster::type	MonsterTest::getMonsterType() const
{
  return (Monster::MONSTERTEST);
}

Missile::AMissile*	MonsterTest::shoot() const
{
  return (nullptr);
}

bool	MonsterTest::move()
{
  // todo + check en fonction de la map
  this->_x -= 1;
  return (1);
}

void	MonsterTest::getHit(AUnit*)
{
  if (this->_hp > 0)
    this->_hp -= 1;
}

}

}
