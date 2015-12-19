#include <algorithm>
#include <string>
#include "AMissile.hpp"
#include "BasicMissile.hpp"
#include "GameUtils.hpp"
#include "Map.hpp"

extern "C"
{
  Unit::Missile::AMissile*	NewMissile(Unit::AUnit* origin, unsigned int id)
  {
    return (new Unit::Missile::BasicMissile(origin, id));
  }

  void	DeleteMissile(Unit::Missile::AMissile* missile)
  {
    delete missile;
  }
}

namespace Unit {

  namespace Missile {

    BasicMissile::BasicMissile(AUnit *origin, unsigned int id)
    : AMissile(std::make_pair(2, 2), 5, origin, id)
    {
    }

    BasicMissile::~BasicMissile()
    {
    }

    bool    BasicMissile::isKillable() const
    {
      return true;
    }

    Missile::type   BasicMissile::getMissileType() const
    {
      return BASIC;
    }

    Unit::pos            BasicMissile::move() const
    {
        uintmax_t diff = GameUtils::Game::now(_gameID) - _creationTime;
      pos p = std::make_pair(_x + diff / 10000, _y + diff / 10000);

      return p;
    }

    double    BasicMissile::getTime() const
    {
      return 1.0;
    }

    std::string     BasicMissile::getClassName() const
    {
      return std::string("BasicMissile");
    }

    void            BasicMissile::getHit(AUnit*)
    {
      _hp = 0;
    }

    AMissile*            BasicMissile::clone(AUnit *unit, unsigned int id) const
    {
      return new BasicMissile(unit, id);
    }
      
    Unit::typeID        BasicMissile::getTypeID() const
    {
        return Unit::BASICMISSILE;
    }
  }

}
