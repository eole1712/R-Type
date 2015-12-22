#include <algorithm>
#include <cmath>
#include <string>

#include "AMissile.hpp"
#include "DirectedMissile.hpp"
#include "GameUtils.hpp"
#include "Map.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport)      Unit::Missile::AMissile*  NewMissile(Unit::AUnit* origin, unsigned int id, Timer::time time);
#endif
    Unit::Missile::AMissile*  NewMissile(Unit::AUnit* origin, unsigned int id, Timer::time time)
  {
    return (new Unit::Missile::DirectedMissile(origin, id, time));
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

      DirectedMissile::DirectedMissile(AUnit *origin, unsigned int id, Timer::time time)
    : AMissile(std::make_pair(20, 14), 5, origin, id, time)
    {
    }

    DirectedMissile::~DirectedMissile()
    {
    }

    bool    DirectedMissile::isKillable() const
    {
      return true;
    }

    Missile::type   DirectedMissile::getMissileType() const
    {
      return WAVE;
    }

      Unit::pos            DirectedMissile::move(Timer::time time) const
    {
        long diff = static_cast<long>(time - _creationTime) / 10;
        
        pos p = std::make_pair(_x + (diff * 5 * (_team == Unit::ALLY ? 1 : -1)), _y + std::sin((diff % 500) / 100.0) * 500.0);
        return p;
    }

    double    DirectedMissile::getTime() const
    {
        return (1.0 / (_origin->getType() == PLAYER ? 3 : 0.2));
    }

    std::string     DirectedMissile::getClassName() const
    {
      return std::string("DirectedMissile");
    }

    void            DirectedMissile::getHit(AUnit*)
    {
      _hp = 0;
    }

      AMissile*            DirectedMissile::clone(AUnit *unit, unsigned int id, Timer::time time) const
    {
      return new DirectedMissile(unit, id, time);
    }

    Unit::typeID        DirectedMissile::getTypeID() const
    {
      return Unit::DirectedMissile;
    }
  }

}
