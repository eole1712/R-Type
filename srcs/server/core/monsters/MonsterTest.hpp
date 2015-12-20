#ifndef MONSTERTEST_H_
# define MONSTERTEST_H_

# include "AUnit.hpp"
# include "AMissile.hpp"

namespace Unit
{
  
  namespace Monster
  {
    
    class MonsterTest : public AMonster
    {
    public:
        MonsterTest(int x, int y, unsigned int id, unsigned int gameID, Timer::time);
      virtual ~MonsterTest();
      
      virtual Monster::type		getMonsterType() const;
      virtual Unit::typeID    getTypeID() const;
      
      virtual Missile::AMissile*	shoot();
      virtual pos     move(Timer::time) const;
      virtual void    getHit(AUnit*);
    };
    
  }
  
}

#endif /* !MONSTERTEST_H_ */
