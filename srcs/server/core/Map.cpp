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
  std::for_each(this->_enemies.begin(), this->_enemies.end(), [](Unit::AUnit* unit)
  {
    delete unit;
  });
}

std::list<Unit::AUnit*> &	Map::getList(Unit::team team)
{
  if (team == Unit::ALLY)
    return (this->_allies);
  return (this->_enemies);
}

void	Map::addUnit(Unit::AUnit* unit)
{
  if (unit->getTeam() == Unit::ALLY)
    this->_allies.push_back(unit);
  else
    this->_enemies.push_back(unit);
}

void            Map::removeUnit(Unit::AUnit* unit)
{
    if (unit->getTeam() == Unit::ALLY)
        _allies.remove(unit);
    else
        _enemies.remove(unit);
}

Unit::AUnit*	Map::checkInterractions(Unit::AUnit* unit) const
{
  Unit::team	team = unit->getTeam();
  auto&	list = ((team != Unit::ALLY) ? (this->_allies) : (this->_enemies));

  for (auto& other : list)
    if (unit->isHitting(other))
      return (other);
  return (nullptr);
}
