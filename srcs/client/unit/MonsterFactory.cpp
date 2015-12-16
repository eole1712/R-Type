#include <map>
#include <list>
#include <algorithm>
#include <utility>
#include "AMonster.hpp"
#include "ILibLoader.hpp"
#include "Game.hpp"

#if (defined __linux__) || (defined __APPLE__)
#include "CULibLoader.hpp"
#elif defined(_WIN32)
#include "CWLibLoader.hpp"
#endif

#include "MonsterFactory.hpp"

const std::map<Unit::Monster::type, std::string> Monster::Factory::LIBSLIST = {
  {Unit::Monster::MONSTERTEST, "../../libs/client/libMonsterTest.so"}
};

namespace Monster {

Factory*     Factory::_instance = NULL;

Factory::Factory()
{
  std::for_each(Monster::Factory::LIBSLIST.begin(), Monster::Factory::LIBSLIST.end(),
		[this](std::pair<Unit::Monster::type, std::string> elem)
		{
		  this->addMonsterType(elem.first, elem.second);
		});
}

Factory::~Factory()
{
  std::for_each(this->_libs.begin(), this->_libs.end(),
		[](std::pair<Unit::Monster::type, ILibLoader*> lib)
		{
		  delete lib.second;
		});
}

Unit::Monster::AMonster*	Factory::createMonster(Unit::Monster::type type, int x, int y,
						       unsigned int id, Time::stamp creationTime)
{
  fptrNewMonster		ptr;
  Unit::Monster::AMonster*	newMonster;

  for(std::list<std::pair<Unit::Monster::type, ILibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	{
	  ptr = reinterpret_cast<fptrNewMonster>((*it).second->getExternalCreator());
	  newMonster = ptr(x, y, id, creationTime);
	  return (newMonster);
	}
    }
  return (NULL);
}

bool	Factory::addMonsterType(Unit::Monster::type type, std::string libName)
{
  ILibLoader*	libLoader;

  for(std::list<std::pair<Unit::Monster::type, ILibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	return (false);
    }

#if (defined __linux__) || (defined __APPLE__)
  libLoader = new CULibLoader(libName, "NewMonster", "DeleteMonster");
#elif defined(_WIN32)
  libLoader = new CWLibLoader(libName, "NewMonster", "DeleteMonster");
#endif

  this->_libs.push_back(std::make_pair(type, libLoader));
  return (true);
}

bool	Factory::removeMonsterType(Unit::Monster::type type)
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

Factory*     Factory::getInstance()
{
  if (_instance == nullptr)
    _instance = new Factory();
  return _instance;
}

void Factory::destroy()
{
  if (_instance == NULL)
    return;
  delete _instance;
  _instance = NULL;
}

}
