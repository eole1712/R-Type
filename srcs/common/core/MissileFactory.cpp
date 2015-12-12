#include "AMissile.hpp"
#include "BasicMissile.hpp"
#include "MissileFactory.hpp"

#include <map>

namespace Unit
{
    namespace Missile
    {

        Factory*	Factory::_instance = NULL;

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
            _map[BASIC] = new BasicMissile(0, 0, NULL, Unit::UP, 0);
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

        AMissile*   Factory::getObject(Missile::type t, unsigned int x, unsigned int y, AUnit *unit, dir d, unsigned int id)
        {
          return (_map[t])->clone(x, y, unit, d, id);
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
