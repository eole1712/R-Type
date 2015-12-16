#include <map>
#include <list>
#include <algorithm>
#include <utility>
#include "AUnit.hpp"
#include "ILibLoader.hpp"
#include "Game.hpp"

#if (defined __linux__) || (defined __APPLE__)
#include "CULibLoader.hpp"
#elif defined(_WIN32)
#include "CWLibLoader.hpp"
#endif

#include "UnitFactory.hpp"

const std::map<Unit::type, std::string> Unit::Factory::LIBSLIST = {
  {Unit::MONSTERTEST, "../../libs/client/libMonsterTest.so"},
  {Unit::BASICMISSILE, "../../libs/client/libBasicMissile.so"}
};

namespace Unit {

Factory*     Factory::_instance = NULL;

Factory::Factory()
{
  std::for_each(Unit::Factory::LIBSLIST.begin(), Unit::Factory::LIBSLIST.end(),
		[this](std::pair<Unit::type, std::string> elem)
		{
		  this->addUnitType(elem.first, elem.second);
		});
}

Factory::~Factory()
{
  std::for_each(this->_libs.begin(), this->_libs.end(),
		[](std::pair<Unit::type, ILibLoader*> lib)
		{
		  delete lib.second;
		});
}

Unit::AUnit*	Factory::createUnit(Unit::type type, int x, int y,
				    unsigned int id, Time::stamp creationTime)
{
  fptrNewUnit	ptr;
  Unit::AUnit*	newUnit;

  for(std::list<std::pair<Unit::type, ILibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	{
	  ptr = reinterpret_cast<fptrNewUnit>((*it).second->getExternalCreator());
	  newUnit = ptr(x, y, id, creationTime);
	  return (newUnit);
	}
    }
  return (NULL);
}

bool	Factory::addUnitType(Unit::type type, std::string libName)
{
  ILibLoader*	libLoader;

  for(std::list<std::pair<Unit::type, ILibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
	return (false);
    }

#if (defined __linux__) || (defined __APPLE__)
  libLoader = new CULibLoader(libName, "NewUnit", "DeleteUnit");
#elif defined(_WIN32)
  libLoader = new CWLibLoader(libName, "NewUnit", "DeleteUnit");
#endif

  this->_libs.push_back(std::make_pair(type, libLoader));
  return (true);
}

bool	Factory::removeUnitType(Unit::type type)
{
  for(std::list<std::pair<Unit::type, ILibLoader*> >::iterator it = this->_libs.begin();
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
