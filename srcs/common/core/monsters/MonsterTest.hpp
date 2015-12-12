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
  MonsterTest(unsigned int x, unsigned int y);
  virtual ~MonsterTest();

  virtual Monster::type		getMonsterType() const;

  virtual Missile::AMissile*	shoot();
  virtual bool			move();
  virtual void			getHit(AUnit*);
};

}

}

#endif /* !MONSTERTEST_H_ */
