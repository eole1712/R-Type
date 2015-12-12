#include <algorithm>
#include <string>
#include "BasicMissile.hpp"
#include "Map.hpp"

namespace Unit {

    namespace Missile {

        BasicMissile::BasicMissile(unsigned int x, unsigned int y, AUnit *origin, dir d)
        : AMissile(x, y, std::make_pair(2, 2), 5, origin, d)
        {
        }

        BasicMissile::BasicMissile()
        : AMissile(0, 0, std::make_pair(2, 2), 5, NULL, LEFT)
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
          static int              tab[4][2] =
          {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
          };
          
          if ((tab[_dir][0] == -1 && !_x) || (tab[_dir][0] == 1 && _x == Map::WIDTH) || (tab[_dir][1] == -1 && !_y) || (tab[_dir][1] == 1 && _y == Map::HEIGHT))
            _hp = 0;
          else
          {
            _x += tab[_dir][0];
            _y += tab[_dir][1];
          }
        }

        double    BasicMissile::getTime() const
        {
            return 1.0;
        }

        std::string     BasicMissile::getClassName() const
        {
            return std::string("BasicMissile");
        }
        
        void            BasicMissile::getHit(AUnit*)
        {
          _hp = 0;
        }
      
        AMissile*            BasicMissile::clone() const
        {
            return new BasicMissile;
        }

        AMissile*            BasicMissile::clone(unsigned int x, unsigned int y, AUnit *unit, dir d) const
        {
            return new BasicMissile(x, y, unit, d);
        }
    }

}