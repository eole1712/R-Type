#include "AUnit.hpp"
#include "ABonus.hpp"

namespace Unit
{

    namespace Bonus
    {

        ABonus::ABonus(int x, int y, Unit::boxType hitBox, unsigned int id, unsigned int gameID)
        : AUnit(1, Unit::ENEMY, x, y, hitBox, id, gameID)
        {}

        ABonus::~ABonus()
        {}

        Unit::type	ABonus::getType() const
        {
            return (Unit::MISSILE);
        }

        pos      ABonus::move() const
        {
	  // TODO : déplacement linéaire vers la gauche en fonction du temps
            return std::make_pair(_x, _y);
        }

    }

}
