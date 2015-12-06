#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include "AMonster.hpp"
#include "ILibLoader.hpp"

#if defined(__linux__)
#include "CULibLoader.hpp"
#elif defined(_WIN32)
#include "CWLibLoader.hpp"
#endif

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
		[](std::pair<Unit::Monster::type, ILibLoader*> lib)
  {
    delete lib.second;
  });
}

Unit::Monster::AMonster*	MonsterFactory::createMonster(Unit::Monster::type type)
{
  fptrNewMonster		ptr;
  Unit::Monster::AMonster*	newMonster;

  for(std::list<std::pair<Unit::Monster::type, ILibLoader*> >::iterator it = this->_libs.begin();
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

bool	MonsterFactory::addMonsterType(Unit::Monster::type type, std::string)
{
  ILibLoader*	libLoader;

  for(std::list<std::pair<Unit::Monster::type, ILibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	return (false);
    }

#if defined(__linux__)
  libLoader = new CULibLoader(libName, "NewMonster", "DeleteMonster");
#elif defined(_WIN32)
  libLoader = new CWLibLoader(libName, "NewMonster", "DeleteMonster");
#endif

  this->_libs.push_back(std::make_pair(type, libLoader));
  return (true);
}

bool	MonsterFactory::removeMonsterType(Unit::Monster::type type)
{
  for(std::list<std::pair<Unit::Monster::type, ILibLoader*> >::iterator it = this->_libs.begin();
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
