#include <list>
#include <algorithm>
#include "AUnit.hpp"
#include "MonsterFactory.hpp"
#include "MissileFactory.hpp"
#include "Map.hpp"
#include "ObjectCast.hpp"

Map::Map()
{}

Map::~Map()
{
  std::for_each(this->_allies.begin(), this->_allies.end(), [](Unit::AUnit* unit)
  {
      if (unit->getType() == Unit::MISSILE)
          Unit::Missile::Factory::getInstance()->deleteUnit(ObjectCast::getObject<Unit::Missile::AMissile*>(unit));
  });
  std::for_each(this->_enemies.begin(), this->_enemies.end(), [](Unit::AUnit* unit)
  {
      if (unit->getType() == Unit::MISSILE)
          Unit::Missile::Factory::getInstance()->deleteUnit(ObjectCast::getObject<Unit::Missile::AMissile*>(unit));
      else if (unit->getType() == Unit::MONSTER)
          Monster::Factory::getInstance()->deleteUnit(ObjectCast::getObject<Unit::Monster::AMonster*>(unit));
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

std::list<Unit::AUnit*>::iterator            Map::removeUnit(Unit::AUnit* unit)
{
    std::list<Unit::AUnit*>::iterator it;
    
    if (unit->getTeam() == Unit::ALLY)
    {
        it = _allies.erase(std::remove(_allies.begin(), _allies.end(), unit), _allies.end());
        
        Unit::Missile::Factory::getInstance()->deleteUnit(ObjectCast::getObject<Unit::Missile::AMissile*>(unit));
    }
    else
    {
        it = _enemies.erase(std::remove(_enemies.begin(), _enemies.end(), unit), _enemies.end());
        
        if (unit->getType() == Unit::MISSILE)
            Unit::Missile::Factory::getInstance()->deleteUnit(ObjectCast::getObject<Unit::Missile::AMissile*>(unit));
        else if (unit->getType() == Unit::MONSTER)
            Monster::Factory::getInstance()->deleteUnit(ObjectCast::getObject<Unit::Monster::AMonster*>(unit));
    }
    return it;
}

Unit::AUnit*	Map::checkInterractions(Unit::AUnit* unit, Timer::time time) const
{
  Unit::team	team = unit->getTeam();
  auto&	list = ((team != Unit::ALLY) ? (this->_allies) : (this->_enemies));

  for (auto& other : list)
    if (unit->isHitting(other, time))
      return (other);
  return (nullptr);
}
