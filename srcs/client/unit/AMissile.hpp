#ifndef AMissile_hpp
#define AMissile_hpp

#include <string>
#include "AUnit.hpp"
#include "Timer.hpp"

namespace Unit {

  namespace Missile {

    enum type {
      BASIC
    };

    class AMissile : public AUnit {
    public:
      AMissile(team, unsigned int x, unsigned int y, unsigned int id, unsigned int gameID,
	       Timer::time creationTime);
      virtual ~AMissile();

    public:
      virtual Missile::type   getMissileType() const = 0;

    public:
      virtual pos             move() const = 0;

    public:
      virtual Unit::type      getType() const;
      virtual double          getTime() const = 0;

    public:
      virtual AMissile*	clone(AUnit*, unsigned int id) const = 0;
      virtual std::string	getClassName() const = 0;
      virtual void	  render(sf::RenderWindow & window) = 0;
    };
  }
}

#endif /* AMissile_hpp */
