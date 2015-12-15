#include "AMonster.hpp"

namespace Unit
{

  namespace Monster
  {

  AMonster::AMonster(int x, int y, unsigned int id, Time::stamp creationTime)
    : AUnit(x, y, id, creationTime)
    {}

    AMonster::~AMonster()
    {}
  }

}
