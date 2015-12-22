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

const std::map<Unit::typeID, std::string> Unit::Factory::LIBSLIST = {
#if (defined __APPLE__)
  { Unit::MONSTERTEST, "../libs/client/libClientMonsterTest.dylib" },
  { Unit::BASICMISSILE, "../libs/client/libClientBasicMissile.dylib" },
  { Unit::BIGHUNTER, "../libs/client/libClientBigHunter.dylib" },
  { Unit::WAVEMISSILE, "../libs/client/libClientWaveMissile.dylib" }
#elif (defined _WIN32)
  { Unit::MONSTERTEST, "..\\libs\\client\\ClientMonsterTest.dll" },
  { Unit::BASICMISSILE, "..\\libs\\client\\ClientBasicMissile.dll" },
  { Unit::BIGHUNTER, "..\\libs\\client\\ClientBigHunter.dll" },
  { Unit::WAVEMISSILE, "..\\libs\\client\\ClientWaveMissile.dll" }
#else
  { Unit::MONSTERTEST, "../libs/client/libClientMonsterTest.so" },
  { Unit::BASICMISSILE, "../libs/client/libClientBasicMissile.so" },
  { Unit::BIGHUNTER, "../libs/client/libClientBigHunter.so" },
  { Unit::WAVEMISSILE, "../libs/client/libClientWaveMissile.so" },
#endif
};

namespace Unit {

  Factory*     Factory::_instance = NULL;

  Factory::Factory()
  {
    std::for_each(Unit::Factory::LIBSLIST.begin(), Unit::Factory::LIBSLIST.end(),
      [this](std::pair<Unit::typeID, std::string> elem)
      {
        this->addUnitType(elem.first, elem.second);
      });
  }

  Factory::~Factory()
  {
    std::for_each(this->_libs.begin(), this->_libs.end(),
      [](std::pair<Unit::typeID, ILibLoader*> lib)
      {
        delete lib.second;
      });
  }

  Unit::AUnit*	Factory::createUnit(Unit::typeID type, int x, int y,
    unsigned int id, Time::stamp creationTime, float param)
  {
    fptrNewUnit	ptr;
    Unit::AUnit*	newUnit;

    for(std::list<std::pair<Unit::typeID, ILibLoader*> >::iterator it = this->_libs.begin();
      it != this->_libs.end(); ++it)
    {
      if ((*it).first == type)
      {
       ptr = reinterpret_cast<fptrNewUnit>((*it).second->getExternalCreator());
       newUnit = ptr(x, y, id, creationTime, param);
       return (newUnit);
     }
   }
   return (NULL);
 }

 void		Factory::deleteUnit(AUnit * unit)
 {
  fptrDeleteUnit	ptr;

  for(std::list<std::pair<Unit::typeID, ILibLoader*> >::iterator it = this->_libs.begin();
    it != this->_libs.end(); ++it)
  {
    if ((*it).first == unit->getType())
    {
     ptr = reinterpret_cast<fptrDeleteUnit>((*it).second->getExternalDestructor());
     ptr(unit);
     return ;
   }
 }
}

bool	Factory::addUnitType(Unit::typeID type, std::string libName)
{
  ILibLoader*	libLoader;

  for(std::list<std::pair<Unit::typeID, ILibLoader*> >::iterator it = this->_libs.begin();
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

bool	Factory::removeUnitType(Unit::typeID type)
{
  for(std::list<std::pair<Unit::typeID, ILibLoader*> >::iterator it = this->_libs.begin();
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
