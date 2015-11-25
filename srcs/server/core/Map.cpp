#include <list>
#include <algorithm>
#include "AUnit.hpp"
#include "Map.hpp"

Map::Map()
{}

Map::~Map()
{
  std::for_each(this->_allies.begin(), this->_allies.end(), [](Unit::AUnit* unit)
  {
    delete unit;
  });
  std::for_each(this->_ennemies.begin(), this->_ennemies.end(), [](Unit::AUnit* unit)
  {
    delete unit;
  });
}

std::list<Unit::AUnit*> const&	getList(Unit::team team) const
{
  if (team == Unit::ALLY)
    return (this->_allies);
  return (this->_ennemies);
}

void	addUnit(Unit::AUnit* unit)
{
  if (unit->getTeam() == Unit::ALLY)
    this->_allies.push_back(unit);
  else
    this->_ennemies.push_back(unit);
}

Unit::AUnit*	checkInterractions(Unit::AUnit* unit) const
{
  Unit::team	team = unit->getTeam();
  auto&	list = ((team == Unit::ALLY) ? (this->_allies) : (this->_ennemies));

  std::for_each(list.begin(), list.end(), [unit](Unit::AUnit* other)
  {
    if (unit->isHitting(other))
      return (other);
  });
  return (nullptr);
}
