#include <utility>
#include "ABonus.hpp"

namespace Unit
{

  namespace Bonus
  {

  ABonus::ABonus(int x, int y, unsigned int id, unsigned int gameID, Time::stamp creationTime)
    : AUnit(Unit::ENEMY, x, y, id, gameID, creationTime)
    {}

    ABonus::~ABonus()
    {}

    pos	ABonus::move() const
    {
      // todo
      return (std::make_pair(0, 0));
    }

  }

}
