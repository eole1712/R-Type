#include <list>
#include <algorithm>
#include <utility>
#include "IMonster.hpp"
#include "MonsterFactory.hpp"

MonsterFactory::MonsterFactory()
{}

MonsterFactory::~MonsterFactory()
{
  std::for_each(this->_libs.begin(), this->_libs.end(), [](std::pair<Monster::type, LibLoader*> lib)
  {
    delete lib.second();
  });
}

IMonster*	MonsterFactory::createMonster(Monster::type type)
{
  fptrNewMonster	ptr;
  IMonster*		newMonster;

  for(std::list<std::pair<Monster::type, LibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if (*it.first() == type)
	{
	  ptr = reinterpret_cast<fptrNewMonster>(*it.second()->getExternalCreator());
	  newMonster = ptr();
	  return (newMonster);
	}
    }
  return (NULL);
}

bool	addMonsterType(Monster::type type, std::string libName)
{
  for(std::list<std::pair<Monster::type, LibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if (*it.first() == type)
	return (false);
    }
  this->_libs.push_back(std::make_pair(type, new LibLoader(libName, "NewMonster", "DeleteMonster")));
  return (true);
}

bool	removeMonsterType(Monster::type type)
{
  for(std::list<std::pair<Monster::type, LibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if (*it.first() == type)
	{
	  delete *it.second();
	  this->_libs.erase(it);
	  return (true);
	}
    }
  return (false);
}
