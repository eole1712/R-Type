#ifndef AMissile_hpp
#define AMissile_hpp

#include "AUnit.hpp"

namespace Unit {
  
  namespace Missile {
    
    enum type {
      BASIC
    };
    
    class AMissile : public AUnit {
    public:
      AMissile(unsigned int x, unsigned int y, boxType hitBox, unsigned int dammage, bool killable, AUnit* origin);
      virtual ~AMissile();
      
    public:
      unsigned int        getDammage() const;
      AUnit*              getOrigin() const;
      
    public:
      virtual bool            isKillable() const = 0;
      virtual Missile::type   getMissileType() const = 0;
      virtual void            move() = 0;
      
    public:
      virtual Unit::type      getType() const;
      
    protected:
      unsigned int            _dammage;
      bool                    _killable;
      AUnit*                  _origin;
    };
  }
}

#endif /* AMissile_hpp */
