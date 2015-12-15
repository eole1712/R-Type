#include "AUnit.hpp"

namespace Unit {

AUnit::AUnit(int x, int y, unsigned int id, Time::stamp creationTime)
  : _x(x), _y(y), _id(id), _creationTime(creationTime)
  {
  }

  AUnit::~AUnit()
  {
  }

  Time::stamp AUnit::getCreationTime() const
  {
    return _creationTime;
  }

  unsigned int  AUnit::getID() const
  {
    return _id;
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
