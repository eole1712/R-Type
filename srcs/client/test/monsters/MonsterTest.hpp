#ifndef MONSTERTEST_H_
# define MONSTERTEST_H_

# include "AUnit.hpp"
# include "AMissile.hpp"
# include "Timer.hpp"

namespace Unit
{

  namespace Monster
  {

    class MonsterTest : public AMonster
    {
    public:
      MonsterTest(int x, int y, unsigned int id, Timer::time creationTime);
      virtual ~MonsterTest();

      virtual Monster::type		getMonsterType() const;

      virtual pos     move() const;
    };

  }

}

#endif /* !MONSTERTEST_H_ */
