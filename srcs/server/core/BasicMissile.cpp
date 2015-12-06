#include <algorithm>
#include <string>
#include "BasicMissile.hpp"

namespace Unit {

    namespace Missile {

        BasicMissile::BasicMissile(unsigned int x, unsigned int y, AUnit *origin)
        : AMissile(x, y, std::make_pair(2, 2), 5, origin)
        {
        }

        BasicMissile::BasicMissile()
        : AMissile(0, 0, std::make_pair(2, 2), 5, NULL)
        {
        }

        BasicMissile::~BasicMissile()
        {
        }

        bool    BasicMissile::isKillable() const
        {
            return true;
        }

        Missile::type   BasicMissile::getMissileType() const
        {
            return BASIC;
        }

        void            BasicMissile::move()
        {
            //TODO: move basic missile
        }

        double    BasicMissile::getTime() const
        {
            return 1.0;
        }

        std::string     BasicMissile::getClassName() const
        {
            return std::string("BasicMissile");
        }

        void            BasicMissile::getHit(AUnit* unit)
        {
            //TODO: get hit missile
	  (void)unit;
        }

        AMissile*            BasicMissile::clone() const
        {
            return new BasicMissile;
        }

        AMissile*            BasicMissile::clone(unsigned int x, unsigned int y, AUnit *unit) const
        {
            return new BasicMissile(x, y, unit);
        }
    }

}
