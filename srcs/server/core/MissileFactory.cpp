#include "AMissile.hpp"
#include "BasicMissile.hpp"
#include "MissileFactory.hpp"

#include <map>

namespace Unit
{
    namespace Missile
    {
        Factory::Factory()
        {
        }
        
        Factory::~Factory()
        {
            for (std::map<Missile::type, AMissile*>::iterator it = _map.begin(); it != _map.end(); it++)
            {
                if ((*it).second != NULL)
                    delete (*it).second;
            }
        }

        void     Factory::init()
        {
          _map[BASIC] = new BasicMissile;
        }
        
        Factory* Factory::getInstance()
        {
            if (_instance == NULL)
            {
              _instance = new Factory();
              _instance->init();
            }
            return (_instance);
        }
      
        AMissile*   Factory::getObject(Missile::type t)
        {
          return (_map[t])->clone();
        }
      
        AMissile*   Factory::getObject(Missile::type t, unsigned int x, unsigned int y, AUnit *unit)
        {
          return (_map[t])->clone(x, y, unit);
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
