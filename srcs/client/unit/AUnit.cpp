#include "Timer.hpp"
#include "AUnit.hpp"

namespace Unit {

AUnit::AUnit(int x, int y, unsigned int id, Timer::time creationTime)
  : _x(x), _y(y), _id(id), _creationTime(creationTime)
  {
  }

  AUnit::~AUnit()
  {
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
