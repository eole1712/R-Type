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
            ABonus(int x, int y, Unit::boxType hitbox, unsigned int id, unsigned int gameID);
            virtual ~ABonus();
          
        public:
            virtual Unit::type      getType() const;
            virtual Bonus::type     getBonusType() const = 0;          
            virtual pos             move() const = 0;
        };
        
    }
    
}

#endif /* !ABONUS_H_ */
