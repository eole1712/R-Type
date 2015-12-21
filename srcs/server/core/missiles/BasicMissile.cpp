#include <algorithm>
#include <cmath>
#include <string>
#include "AMissile.hpp"
#include "BasicMissile.hpp"
#include "GameUtils.hpp"
#include "Map.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport)      Unit::Missile::AMissile*  NewMissile(Unit::AUnit* origin, unsigned int id, Timer::time time);
#endif
    Unit::Missile::AMissile*  NewMissile(Unit::AUnit* origin, unsigned int id, Timer::time time)
  {
    return (new Unit::Missile::BasicMissile(origin, id, time));
  }

#if (defined _WIN32)
  __declspec(dllexport)     void  DeleteMissile(Unit::Missile::AMissile* missile);
#endif
  void	DeleteMissile(Unit::Missile::AMissile* missile)
  {
    delete missile;
  }
}

namespace Unit {

  namespace Missile {

      BasicMissile::BasicMissile(AUnit *origin, unsigned int id, Timer::time time)
    : AMissile(std::make_pair(20, 14), 5, origin, id, time)
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

      Unit::pos            BasicMissile::move(Timer::time time) const
    {
        long diff = static_cast<long>(time - _creationTime) / 10;
        
        pos p = std::make_pair(_x + (diff * 5 * (_team == Unit::ALLY ? 1 : -1)), _y);
        return p;
    }

    double    BasicMissile::getTime() const
    {
        return (1.0 / (_origin->getType() == PLAYER ? 5 : 0.2));
    }

    std::string     BasicMissile::getClassName() const
    {
      return std::string("BasicMissile");
    }

    void            BasicMissile::getHit(AUnit*)
    {
      _hp = 0;
    }

      AMissile*            BasicMissile::clone(AUnit *unit, unsigned int id, Timer::time time) const
    {
      return new BasicMissile(unit, id, time);
    }

    Unit::typeID        BasicMissile::getTypeID() const
    {
      return Unit::BASICMISSILE;
    }
  }

}
