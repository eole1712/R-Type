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
	  AMonster(int x, int y, unsigned int id, unsigned int gameID, Time::stamp creationTime);
	  virtual ~AMonster();

	  virtual Unit::type          getType() const;
	  virtual Monster::type       getMonsterType() const = 0;

	  virtual pos                 move() const = 0;
	  virtual void		      render(sf::RenderWindow & window) = 0;
        };

    }

}

#endif /* !AMONSTER_H_ */
