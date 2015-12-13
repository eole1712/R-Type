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
  Unit::Monster::AMonster*	NewMonster(int x, int y, unsigned int id, unsigned int gameID)
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
    
    MonsterTest::MonsterTest(int x, int y, unsigned int id, unsigned int gameID)
    : AMonster(1, x, y, std::make_pair(5, 5), Missile::BASIC, id, gameID)
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
      
      Missile::AMissile *m = Missile::Factory::getInstance()->getObject(_weapon, this, Game::getNewID(_gameID));
      
      _time.reset(m->getTime());
      return m;
    }
    
    Unit::pos            MonsterTest::move() const
    {
      uintmax_t diff = Game::now(_gameID) - _creationTime;
      pos p = std::make_pair(_x + diff / 10000, _y + diff / 10000);
      
      return p;
    }
    
    void	MonsterTest::getHit(AUnit*)
    {
      if (this->_hp > 0)
        this->_hp -= 1;
    }
    
  }
  
}
