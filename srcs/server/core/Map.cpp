#include <list>
#include <algorithm>
#include "AUnit.hpp"
#include "Map.hpp"

Map::Map()
{}

Map::~Map()
{
  std::for_each(this->_allies.begin(), this->_allies.end(), [](AUnit* unit)
  {
    delete unit;
  });
  std::for_each(this->_ennemies.begin(), this->_ennemies.end(), [](AUnit* unit)
  {
    delete unit;
  });
}

std::list<AUnit*> const&	getList(Unit::team team) const
{
  if (team == Unit::ALLY)
    return (this->_allies);
  return (this->_ennemies);
}

void	addUnit(AUnit* unit)
{
  if (unit->getTeam() == Unit::ALLY)
    this->_allies.push_back(unit);
  else
    this->_ennemies.push_back(unit);
}

AUnit*	checkInterractions(AUnit* unit) const
{
  Unit::team	team = unit->getTeam();
  auto&	list = ((team == Unit::ALLY) ? (this->_allies) : (this->_ennemies));

  std::for_each(list.begin(), list.end(), [unit](AUnit* other)
  {
    if (unit->isHitting(other))
      return (other);
  });
  return (nullptr);
}
