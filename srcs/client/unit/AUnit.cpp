#include <utility>
#include "AUnit.hpp"
#include "Time.hpp"

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

pos	AUnit::move(Time::stamp tick) const
{
  int	diff = static_cast<long>(tick - _creationTime) / 10;

  return {_x + diff, _y}
}

}
