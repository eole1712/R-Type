#include "AMissile.hpp"

namespace Unit {
  namespace Missile {

    AMissile::AMissile(int x, int y, unsigned int id, Time::stamp creationTime)
      : AUnit(x, y, id, creationTime)
    {
    }

    AMissile::~AMissile()
    {
    }
  }
}
