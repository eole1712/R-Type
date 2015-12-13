#ifndef FactoryUnit_hpp
#define FactoryUnit_hpp

#include <stdio.h>

#include "AUnit.hpp"

namespace Unit {
  class FactoryUnit : public AUnit
  {
  public:
      FactoryUnit();
      ~FactoryUnit();
  public:
      void  getHit(AUnit*);
      pos   move() const;
      type  getType() const;
  };
}

#endif /* FactoryUnit_hpp */
