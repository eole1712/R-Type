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
      MonsterTest(int x, int y, unsigned int id, unsigned int gameID);
      virtual ~MonsterTest();
      
      virtual Monster::type		getMonsterType() const;
      
      virtual Missile::AMissile*	shoot();
      virtual pos     move() const;
      virtual void    getHit(AUnit*);
    };
    
  }
  
}

#endif /* !MONSTERTEST_H_ */
