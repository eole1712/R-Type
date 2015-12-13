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

    void		ABonus::render(sf::RenderWindow & window)
	{
  
	}
  }
  
}
