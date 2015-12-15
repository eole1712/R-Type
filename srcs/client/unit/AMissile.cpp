#include "AMissile.hpp"

namespace Unit {
  namespace Missile {

    AMissile::AMissile(unsigned int x, unsigned int y,
		       unsigned int id, unsigned int gameID,
		       Time::stamp creationTime)
      : AUnit(t, x, y, id, gameID, creationTime)
    {
    }

    AMissile::~AMissile()
    {
    }
  }
}
