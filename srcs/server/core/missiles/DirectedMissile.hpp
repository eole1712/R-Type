#ifndef DIRECTEDMISSILE_H_
#define DIRECTEDMISSILE_H_

#include "AMissile.hpp"

namespace Unit {
  
  namespace Missile {
    
    class DirectedMissile : public AMissile{
    public:
        DirectedMissile(AUnit *origin, unsigned int id, Timer::time);
      virtual ~DirectedMissile();
      
    public:
      virtual bool                isKillable() const;
      virtual Missile::type       getMissileType() const;
      virtual pos                 move(Timer::time) const;
      
    public:
      virtual double              getTime() const;
      virtual Unit::typeID    getTypeID() const;

    public:
      virtual void                getHit(AUnit*);
      
    public:
        virtual AMissile*	clone(AUnit*, unsigned int id, Timer::time) const;
      virtual std::string	getClassName() const;
    };
  }
}

#endif /* DIRECTEDMISSILE_H_ */
