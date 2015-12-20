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
            AMonster(unsigned int hp, int x, int y, boxType hitBox, Missile::type weapon,
                     unsigned int id, unsigned int gameID, Timer::time);
            virtual ~AMonster();

            virtual Unit::type          getType() const;
            virtual Monster::type       getMonsterType() const = 0;
            virtual Unit::typeID        getTypeID() const = 0;

            virtual Missile::AMissile*  shoot(Timer::time);
            virtual pos                 move(Timer::time) const = 0;

        protected:
            Missile::type     _weapon;
            Timer             _time;
        };

    }

}

#endif /* !AMONSTER_H_ */
