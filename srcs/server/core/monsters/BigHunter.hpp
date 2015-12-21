#ifndef BIGHUNTER_H_
# define BIGHUNTER_H_

# include "AUnit.hpp"
# include "AMissile.hpp"

namespace Unit
{
  
  namespace Monster
  {
    
    class BigHunter : public AMonster
    {
    public:
        BigHunter(int x, int y, unsigned int id, unsigned int gameID, Timer::time);
      virtual ~BigHunter();
      
      virtual Monster::type		getMonsterType() const;
      virtual Unit::typeID    getTypeID() const;
      
        virtual Missile::AMissile*	shoot(Timer::time time);
      virtual pos     move(Timer::time) const;
      virtual void    getHit(AUnit*);
    };
    
  }
  
}

#endif /* !BIGHUNTER_H_ */
