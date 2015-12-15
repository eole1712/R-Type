#ifndef ABONUS_H_
# define ABONUS_H_

# include "AUnit.hpp"
# include "Timer.hpp"

namespace Unit
{

    namespace Bonus
    {

        enum type {
            BASIC
        };

        class ABonus : public AUnit
        {
        public:
	  ABonus(int x, int y, unsigned int id, unsigned int gameID, Timer::time creationTime);
	  virtual ~ABonus();

        public:
            virtual Unit::type      getType() const;
            virtual Bonus::type     getBonusType() const = 0;
            virtual pos             move() const;
        };

    }

}

#endif /* !ABONUS_H_ */
