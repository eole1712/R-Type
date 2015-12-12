#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "MissileFactory.hpp"

namespace Unit
{
  
  namespace Monster
  {
    
    AMonster::AMonster(unsigned int hp, unsigned int x, unsigned int y,
                       Unit::boxType hitBox, Missile::type weapon, dir d, unsigned int id)
    : AUnit(hp, Unit::ENEMY, x, y, hitBox, d, id), _weapon(weapon), _time(0)
    {}
    
    AMonster::~AMonster()
    {}
    
    Unit::type	AMonster::getType() const
    {
      return (Unit::MONSTER);
    }
    
    Missile::AMissile*          AMonster::shoot()
    {
      if (!_time.isFinished())
        return NULL;
      
      Missile::AMissile *m = Missile::Factory::getInstance()->getObject(_weapon, _x, _y, this, _dir, 0);
      
      _time.reset(m->getTime());
      
      return m;
    }
  }
  
}
