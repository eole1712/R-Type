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
        AMissile(boxType hitBox, unsigned int dammage, AUnit* origin, unsigned int id);
      virtual ~AMissile();

    public:
      unsigned int        getDammage() const;
      AUnit*              getOrigin() const;

    public:
      virtual bool            isKillable() const = 0;
      virtual Missile::type   getMissileType() const = 0;
      
    public:
      virtual pos             move() const = 0;

    public:
      virtual void	      render(sf::RenderWindow & window);
      virtual Unit::type      getType() const;
      virtual double          getTime() const = 0;

    public:
        virtual AMissile*	clone(AUnit*, unsigned int id) const = 0;
        virtual std::string	getClassName() const = 0;

    protected:
      unsigned int            _dammage;
      AUnit*                  _origin;
    };
  }
}

#endif /* AMissile_hpp */
