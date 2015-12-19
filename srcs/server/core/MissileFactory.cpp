#include <string>
#include <map>
#include <list>
#include <algorithm>
#include <utility>
#include "AMissile.hpp"
#include "ILibLoader.hpp"

#if (defined __linux__) || (defined __APPLE__)
#include "CULibLoader.hpp"
#elif defined(_WIN32)
#include "CWLibLoader.hpp"
#endif

#include "MissileFactory.hpp"

const std::map<Unit::Missile::type, std::string> Unit::Missile::Factory::LIBSLIST = {
  {
#if (defined __APPLE__)
      Unit::Missile::BASIC, "../libs/server/libServerBasicMissile.dylib"
#else
      Unit::Missile::BASIC, "../libs/server/libServerBasicMissile.so"
#endif
  }
};

namespace Unit
{
    namespace Missile
    {

    Factory*	Factory::_instance = NULL;

    Factory::Factory()
    {
      std::for_each(Missile::Factory::LIBSLIST.begin(), Missile::Factory::LIBSLIST.end(),
		    [this](std::pair<Unit::Missile::type, std::string> elem)
		    {
		      this->addMissileType(elem.first, elem.second);
		    });
    }

    Factory::~Factory()
    {
      std::for_each(this->_libs.begin(), this->_libs.end(),
		    [](std::pair<Unit::Missile::type, ILibLoader*> lib)
		    {
		      delete lib.second;
		    });
    }

    Unit::Missile::AMissile*	Factory::createMissile(Unit::Missile::type type, Unit::AUnit* origin,
						       unsigned int id)
    {
        fptrNewMissile			ptr;
        Unit::Missile::AMissile*	newMissile;

        for(std::list<std::pair<Unit::Missile::type, ILibLoader*> >::iterator it = this->_libs.begin();
            it != this->_libs.end(); ++it)
        {
            if ((*it).first == type)
            {
                ptr = reinterpret_cast<fptrNewMissile>((*it).second->getExternalCreator());
		newMissile = ptr(origin, id);
                return (newMissile);
            }
        }
        return (NULL);
    }

    bool	Factory::addMissileType(Unit::Missile::type type, std::string libName)
    {
        ILibLoader*	libLoader;

        for(std::list<std::pair<Unit::Missile::type, ILibLoader*> >::iterator it = this->_libs.begin();
            it != this->_libs.end(); ++it)
        {
            if ((*it).first == type)
                return (false);
        }

#if (defined __linux__) || (defined __APPLE__)
        libLoader = new CULibLoader(libName, "NewMissile", "DeleteMissile");
#elif defined(_WIN32)
        libLoader = new CWLibLoader(libName, "NewMissile", "DeleteMissile");
#endif

        this->_libs.push_back(std::make_pair(type, libLoader));
        return (true);
    }

    bool	Factory::removeMissileType(Unit::Missile::type type)
    {
        for(std::list<std::pair<Unit::Missile::type, ILibLoader*> >::iterator it = this->_libs.begin();
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

    Factory* Factory::getInstance()
    {
      if (_instance == NULL)
	_instance = new Factory();
      return (_instance);
    }

    void Factory::destroy()
    {
      if (_instance == NULL)
	return;
      delete _instance;
      _instance = NULL;
    }
}

}
