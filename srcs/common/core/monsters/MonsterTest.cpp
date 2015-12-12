#include <utility>
#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "MonsterTest.hpp"
#include "MissileFactory.hpp"
#include "Timer.hpp"
#include "Game.hpp"

// ébauche de classe pour test

extern "C"
{
  Unit::Monster::AMonster*	NewMonster(unsigned int x, unsigned int y, unsigned int id, unsigned int gameID)
  {
    return (new Unit::Monster::MonsterTest(x, y, id, gameID));
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

MonsterTest::MonsterTest(unsigned int x, unsigned int y, unsigned int id, unsigned int gameID)
  : AMonster(1, x, y, std::make_pair(5, 5), Missile::BASIC, LEFT, id, gameID)
{}

MonsterTest::~MonsterTest()
{}

Monster::type	MonsterTest::getMonsterType() const
{
  return (Monster::MONSTERTEST);
}

Missile::AMissile*	MonsterTest::shoot()
{
    if (!_time.isFinished())
        return NULL;
    
  Missile::AMissile *m = Missile::Factory::getInstance()->getObject(_weapon, _x, _y, this, _dir, Game::getNewID(_gameID));
    
    _time.reset(m->getTime());
    return m;
}

bool    MonsterTest::move()
{
  if (_x == 0)
    _hp = 0;
  else
    this->_x -= 1;
  return true;
}

void	MonsterTest::getHit(AUnit*)
{
    if (this->_hp > 0)
        this->_hp -= 1;
}

}

}
