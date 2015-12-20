#include "FactoryUnit.hpp"

#include "AUnit.hpp"

namespace Unit
{
  FactoryUnit::FactoryUnit()
  : AUnit(0, ALLY, 0, 0, std::make_pair(0, 0), 0, 0, 0)
  {
  }
  
  FactoryUnit::~FactoryUnit()
  {
  }
  
  void        FactoryUnit::getHit(AUnit*)
  {
    
  }
  
  pos         FactoryUnit::move() const
  {
    return std::make_pair(0, 0);
  }
  
  type        FactoryUnit::getType() const
  {
    return MISSILE;
  }
}