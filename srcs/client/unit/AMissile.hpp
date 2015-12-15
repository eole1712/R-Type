#ifndef AMISSILE_hpp
#define AMISSILE_hpp

#include <string>
#include "AUnit.hpp"

namespace Unit {

  namespace Missile {

    enum type {
      BASIC
    };

    class AMissile : public AUnit {
    public:
      AMissile(int x, int y, unsigned int id, Time::stamp creationTime);
      virtual ~AMissile();

    public:
      virtual Missile::type   getMissileType() const = 0;
      virtual pos             move(Time::stamp) const = 0;
      virtual void	      render(Time::stamp tick, sf::RenderWindow & window) = 0;
    };
  }
}

#endif /* AMISSILE_hpp */
