#ifndef ABONUS_H_
# define ABONUS_H_

# include "AUnit.hpp"

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
	  ABonus(int x, int y, unsigned int id, Time::stamp creationTime);
	  virtual ~ABonus();
	  
        public:
	  virtual pos             move() const;
	  
	  virtual pos             move(Time::stamp) const = 0;
	  virtual void		  render(Time::stamp tick, sf::RenderWindow & window) = 0;
        };

    }

}

#endif /* !ABONUS_H_ */
