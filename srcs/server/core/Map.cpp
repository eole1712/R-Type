#include <list>
#include <algorithm>
#include "AUnit.hpp"
#include "Map.hpp"

const unsigned int Map::width = 720;
const unsigned int Map::height = 480;

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

std::list<Unit::AUnit*> const&	Map::getList(Unit::team team) const
{
  if (team == Unit::ALLY)
    return (this->_allies);
  return (this->_ennemies);
}

void	Map::addUnit(Unit::AUnit* unit)
{
  if (unit->getTeam() == Unit::ALLY)
    this->_allies.push_back(unit);
  else
    this->_ennemies.push_back(unit);
}

Unit::AUnit*	Map::checkInterractions(Unit::AUnit* unit) const
{
  Unit::team	team = unit->getTeam();
  auto&	list = ((team == Unit::ALLY) ? (this->_allies) : (this->_ennemies));

  for (auto& other : list)
    if (unit->isHitting(other))
      return (other);
  return (nullptr);
}