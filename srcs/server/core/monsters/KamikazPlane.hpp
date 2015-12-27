#ifndef KAMIKAZPLANE_H_
# define KAMIKAZPLANE_H_

# include "AUnit.hpp"
# include "AMissile.hpp"

namespace Unit
{
  
  namespace Monster
  {
    
    class KamikazPlane : public AMonster
    {
    public:
        KamikazPlane(int x, int y, unsigned int id, unsigned int gameID, Timer::time);
      virtual ~KamikazPlane();
      
      virtual Monster::type		getMonsterType() const;
      virtual Unit::typeID    getTypeID() const;
      
        virtual Missile::AMissile*	shoot(Timer::time time);
      virtual pos     move(Timer::time) const;
      virtual void    getHit(AUnit*);
    };
    
  }
  
}

#endif /* !KAMIKAZPLANE_H_ */
