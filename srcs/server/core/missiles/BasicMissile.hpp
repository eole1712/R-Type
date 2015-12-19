#ifndef BasicMissile_hpp
#define BasicMissile_hpp

#include "AMissile.hpp"

namespace Unit {
  
  namespace Missile {
    
    class BasicMissile : public AMissile{
    public:
      BasicMissile(AUnit *origin, unsigned int id);
      virtual ~BasicMissile();
      
    public:
      virtual bool                isKillable() const;
      virtual Missile::type       getMissileType() const;
      virtual pos                 move() const;
      
    public:
      virtual double              getTime() const;
      virtual Unit::typeID    getTypeID() const;

    public:
      virtual void                getHit(AUnit*);
      
    public:
      virtual AMissile*	clone(AUnit*, unsigned int id) const;
      virtual std::string	getClassName() const;
    };
  }
}

#endif /* BasicMissile_hpp */
