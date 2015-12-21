#include <iostream>
#include "Timer.hpp"
#include "AUnit.hpp"
#include "GameUtils.hpp"

namespace Unit {
    
    AUnit::AUnit(unsigned int hp, team t, int x, int y, boxType hitBox, unsigned int id, unsigned int gameID, Timer::time time)
    : _hp(hp), _team(t), _x(x), _y(y), _hitBox(hitBox), _id(id), _gameID(gameID), _creationTime(time)
    {
    }
    
    AUnit::~AUnit()
    {
    }
    
    bool    AUnit::isAlive(Timer::time time) const
    {
        //DEBUG: player invincible
        if (getType() == PLAYER)
            return true;

        if ((getType() == MONSTER || getType() == MISSILE) && GameUtils::Map::isIn(getX(time), getY(time)) == false)
            return (false);
        return (_hp > 0);
    }
    
    boxType     AUnit::getHitBox() const
    {
        return _hitBox;
    }
    
    void        AUnit::setHitBox(boxType hitBox)
    {
        _hitBox = hitBox;
    }
    
    team        AUnit::getTeam() const
    {
        return _team;
    }
    
    void        AUnit::setTeam(team t)
    {
        _team = t;
    }
    
    unsigned int  AUnit::getID() const
    {
        return _id;
    }
    
    unsigned int  AUnit::getGameID() const
    {
        return _gameID;
    }
    
    Timer::time AUnit::getCreationTime() const
    {
        return _creationTime;
    }
    
    int    AUnit::getX(Timer::time time) const
    {
        return move(time).first;
    }
    
    int    AUnit::getY(Timer::time time) const
    {
        return move(time).second;
    }
    
    bool        AUnit::isHitting(AUnit *unit, Timer::time time) const
    {
        if ((max(getX(time), unit->getX(time)) < min(getX(time) + _hitBox.first, unit->getX(time) + unit->getHitBox().first)) && (max(getY(time), unit->getY(time)) < min(getY(time) + _hitBox.second, unit->getY(time) + unit->getHitBox().second)))
            return true;
        return false;
    }
    
    int         AUnit::getStartX() const
    {
        return _x;
    }

    int         AUnit::getStartY() const
    {
        return _y;
    }
    
    void         AUnit::setID(unsigned int id)
    {
        _id = id;
    }
}
