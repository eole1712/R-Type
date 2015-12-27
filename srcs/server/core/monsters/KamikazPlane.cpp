#include <cmath>
#include <utility>
#include "AUnit.hpp"
#include "AMissile.hpp"
#include "AMonster.hpp"
#include "KamikazPlane.hpp"
#include "MissileFactory.hpp"
#include "Timer.hpp"
#include "GameUtils.hpp"

// ébauche de classe pour test

extern "C"
{
#if (defined _WIN32)
  __declspec(dllexport)        Unit::Monster::AMonster* NewMonster(int x, int y, unsigned int id, unsigned int gameID, Timer::time time);
#endif
    Unit::Monster::AMonster*  NewMonster(int x, int y, unsigned int id, unsigned int gameID, Timer::time time)
  {
    return (new Unit::Monster::KamikazPlane(x, y, id, gameID, time));
  }
  
#if (defined _WIN32)
  __declspec(dllexport)     void  DeleteMonster(Unit::Monster::AMonster* monster);
#endif
  void	DeleteMonster(Unit::Monster::AMonster* monster)
  {
    delete monster;
  }
}

namespace Unit
{

  namespace Monster
  {

      KamikazPlane::KamikazPlane(int x, int y, unsigned int id, unsigned int gameID, Timer::time time)
    : AMonster(1, x, y, std::make_pair(39, 49), Missile::BASIC, id, gameID, time)
    {}

    KamikazPlane::~KamikazPlane()
    {}

    Monster::type	KamikazPlane::getMonsterType() const
    {
      return (Monster::KAMIKAZPLANE);
    }

      Missile::AMissile*	KamikazPlane::shoot(Timer::time)
    {
        return nullptr;
    }

      Unit::pos            KamikazPlane::move(Timer::time time) const
    {
      int diff = static_cast<int>((time - _creationTime) / 10);

      pos p = std::make_pair(_x - (diff * 6), _y);
      return p;
    }

    void	KamikazPlane::getHit(AUnit*)
    {
      if (this->_hp > 0)
        this->_hp -= 1;
    }

    Unit::typeID  KamikazPlane::getTypeID() const
    {
      return Unit::KAMIKAZPLANE;
    }

  }

}
