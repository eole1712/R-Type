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
      AMissile(team, unsigned int x, unsigned int y, unsigned int id, unsigned int gameID,
	       Time::stamp creationTime);
      virtual ~AMissile();

    public:
      virtual Missile::type   getMissileType() const = 0;
      virtual pos             move() const = 0;
      virtual void	      render(sf::RenderWindow & window) = 0;
    };
  }
}

#endif /* AMISSILE_hpp */
