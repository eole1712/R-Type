#ifndef IGameUnitSender_hpp
#define IGameUnitSender_hpp

#include "AUnit.hpp"

class       IGameUnitSender
{
public:
    virtual ~IGameUnitSender() {}
    
public:
    virtual void        sendUnit(Unit::AUnit *unit, unsigned int unitType) = 0;
    virtual void        killUnit(Unit::AUnit *unit) = 0;
};

#endif /* IGameUnitSender_hpp */
