#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include "AMonster.hpp"
#include "LibLoader.hpp"
#include "MonsterFactory.hpp"

MonsterFactory::MonsterFactory()
{}

MonsterFactory::MonsterFactory(std::map<Unit::Monster::type, std::string> list)
{
  std::for_each(list.begin(), list.end(),
		[this](std::pair<Unit::Monster::type, std::string> elem)
  {
    this->addMonsterType(elem.first, elem.second);
  });
}

MonsterFactory::~MonsterFactory()
{
  std::for_each(this->_libs.begin(), this->_libs.end(),
		[](std::pair<Unit::Monster::type, LibLoader*> lib)
  {
    delete lib.second;
  });
}

Unit::Monster::AMonster*	MonsterFactory::createMonster(Unit::Monster::type type)
{
  fptrNewMonster		ptr;
  Unit::Monster::AMonster*	newMonster;

  for(std::list<std::pair<Unit::Monster::type, LibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	{
	  ptr = reinterpret_cast<fptrNewMonster>((*it).second->getExternalCreator());
	  newMonster = ptr();
	  return (newMonster);
	}
    }
  return (NULL);
}

bool	MonsterFactory::addMonsterType(Unit::Monster::type type, std::string libName)
{
  for(std::list<std::pair<Unit::Monster::type, LibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	return (false);
    }
  this->_libs.push_back(std::make_pair(type, new LibLoader(libName, "NewMonster", "DeleteMonster")));
  return (true);
}

bool	MonsterFactory::removeMonsterType(Unit::Monster::type type)
{
  for(std::list<std::pair<Unit::Monster::type, LibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	{
	  delete (*it).second;
	  this->_libs.erase(it);
	  return (true);
	}
    }
  return (false);
}
