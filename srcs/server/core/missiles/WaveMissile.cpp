#include <algorithm>
#include <cmath>
#include <string>
#include "AMissile.hpp"
#include "WaveMissile.hpp"
#include "GameUtils.hpp"
#include "Map.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport)      Unit::Missile::AMissile*  NewMissile(Unit::AUnit* origin, unsigned int id, Timer::time time);
#endif
    Unit::Missile::AMissile*  NewMissile(Unit::AUnit* origin, unsigned int id, Timer::time time)
  {
    return (new Unit::Missile::WaveMissile(origin, id, time));
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

      WaveMissile::WaveMissile(AUnit *origin, unsigned int id, Timer::time time)
    : AMissile(std::make_pair(20, 14), 5, origin, id, time)
    {
    }

    WaveMissile::~WaveMissile()
    {
    }

    bool    WaveMissile::isKillable() const
    {
      return true;
    }

    Missile::type   WaveMissile::getMissileType() const
    {
      return WAVE;
    }

      Unit::pos            WaveMissile::move(Timer::time time) const
    {
        long diff = static_cast<long>(time - _creationTime) / 10;
        
        pos p = std::make_pair(_x + (diff * 5 * (_team == Unit::ALLY ? 1 : -1)), _y + std::sin((diff % 2600) / 100.0) * 100.0);
        return p;
    }

    double    WaveMissile::getTime() const
    {
        return (1.0 / (_origin->getType() == PLAYER ? 3 : 0.2));
    }

    std::string     WaveMissile::getClassName() const
    {
      return std::string("WaveMissile");
    }

    void            WaveMissile::getHit(AUnit*)
    {
      _hp = 0;
    }

      AMissile*            WaveMissile::clone(AUnit *unit, unsigned int id, Timer::time time) const
    {
      return new WaveMissile(unit, id, time);
    }

    Unit::typeID        WaveMissile::getTypeID() const
    {
      return Unit::WAVEMISSILE;
    }
  }

}
