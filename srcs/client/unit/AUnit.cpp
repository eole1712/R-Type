#include "Timer.hpp"
#include "AUnit.hpp"

namespace Unit {

AUnit::AUnit(team t, int x, int y, unsigned int id, Timer::time creationTime)
  : _team(t), _x(x), _y(y), _id(id), _creationTime(creationTime)
  {
  }

  AUnit::~AUnit()
  {
  }

  team        AUnit::getTeam() const
  {
    return _team;
  }

  unsigned int  AUnit::getID() const
  {
    return _id;
  }

  Timer::time AUnit::getCreationTime() const
  {
    return _creationTime;
  }

  int    AUnit::getX() const
  {
    return move().first;
  }

  int    AUnit::getY() const
  {
    return move().second;
  }

}
