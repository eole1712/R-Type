#ifndef AMONSTER_H_
# define AMONSTER_H_

# include "AUnit.hpp"

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
	  AMonster(int x, int y, unsigned int id, Time::stamp creationTime);
	  virtual ~AMonster();

	  virtual pos                 move(Time::stamp) const = 0;
	  virtual void		      render(Time::stamp tick, sf::RenderWindow & window) = 0;
        };

    }

}

#endif /* !AMONSTER_H_ */
