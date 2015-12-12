#ifndef AMissile_hpp
#define AMissile_hpp

#include <string>
#include "AUnit.hpp"

namespace Unit {

  namespace Missile {

    enum type {
      BASIC
    };

    class AMissile : public AUnit {
    public:
      AMissile(unsigned int x, unsigned int y, boxType hitBox, unsigned int dammage, AUnit* origin, dir);
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
      virtual double          getTime() const = 0;

    public:
        virtual AMissile*	clone() const = 0;
        virtual AMissile*	clone(unsigned int x, unsigned int y, AUnit*, dir) const = 0;
        virtual std::string	getClassName() const = 0;

    protected:
      unsigned int            _dammage;
      AUnit*                  _origin;
    };
  }
}

#endif /* AMissile_hpp */
