//
//  ObjectCast.hpp
//  R-Type
//
//  Created by Grisha Ghukasyan on 07/12/2015.
//  Copyright © 2015 Grisha Ghukasyan. All rights reserved.
//

#ifndef ObjectCast_hpp
#define ObjectCast_hpp

#include "AUnit.hpp"

namespace ObjectCast {
  
  template<typename T>
  T      getObject(Unit::AUnit *unit)
  {
    return static_cast<T>(unit);
  }
}

#endif /* ObjectCast_hpp */
