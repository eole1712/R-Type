#ifndef AMONSTER_H_
# define AMONSTER_H_

# include "AUnit.hpp"
# include "AMissile.hpp"
# include "Timer.hpp"

namespace Unit
{

    namespace Monster
    {

        enum type {
            MONSTERTEST
        };

        class AMonster : public AUnit
        {
        public:
	  AMonster(int x, int y, unsigned int id, unsigned int gameID, Timer::time creationTime);
	  virtual ~AMonster();

	  virtual Unit::type          getType() const;
	  virtual Monster::type       getMonsterType() const = 0;

	  virtual pos                 move() const = 0;
        };

    }

}

#endif /* !AMONSTER_H_ */
