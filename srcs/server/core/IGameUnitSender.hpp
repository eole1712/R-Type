#ifndef IGameUnitSender_hpp
#define IGameUnitSender_hpp

#include "AUnit.hpp"

class       IGameUnitSender
{
public:
    ~IGameUnitSender();
    
public:
    void        sendUnit(Unit::AUnit *unit, unsigned int unitType) = 0;
};

#endif /* IGameUnitSender_hpp */
