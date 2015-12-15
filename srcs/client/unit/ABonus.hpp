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
	  ABonus(int x, int y, unsigned int id, unsigned int gameID, Time::stamp creationTime);
	  virtual ~ABonus();
	  
        public:
	  virtual pos             move() const;
	  
	  virtual Bonus::type     getBonusType() const = 0;
	  virtual void		  render(sf::RenderWindow & window) = 0;
        };

    }

}

#endif /* !ABONUS_H_ */
