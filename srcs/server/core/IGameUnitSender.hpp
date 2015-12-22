#ifndef IGameUnitSender_hpp
#define IGameUnitSender_hpp

#include "AUnit.hpp"

class       IGameUnitSender
{
public:
    virtual ~IGameUnitSender() {}
    
public:
	virtual void	    Server::refreshTimer(unsigned int idGame, Timer::time time);
    virtual void        sendUnit(Unit::AUnit *unit, unsigned int unitType) = 0;
    virtual void        killUnit(unsigned int id, unsigned int gameID) = 0;
};

#endif /* IGameUnitSender_hpp */
