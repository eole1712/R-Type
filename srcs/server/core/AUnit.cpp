#include <iostream>
#include "Timer.hpp"
#include "AUnit.hpp"
#include "GameUtils.hpp"

namespace Unit {
    
    AUnit::AUnit(unsigned int hp, team t, int x, int y, boxType hitBox, unsigned int id, unsigned int gameID, Timer::time time)
    : _hp(hp), _alive(true), _team(t), _x(x), _y(y), _tX(x), _tY(y), _t(0), _hitBox(hitBox), _id(id), _gameID(gameID), _creationTime(time)
    {
    }
    
    AUnit::~AUnit()
    {
    }
    
    bool    AUnit::healthCheck(Timer::time time)
    {
        //DEBUG: player invincible
//        if (getType() == PLAYER)
//            return true;
        if (!_alive)
            return false;
        if ((getType() == MONSTER || getType() == MISSILE) && GameUtils::Map::isInBox(getX(time), getY(time), _hitBox.first) == false)
            return false;
        if (GameUtils::Map::isInBas(getY(time), _hitBox.second) == false)
            return false;
        if (_hp == 0)
            return false;
        return true;
    }
    
    bool    AUnit::isAlive() const
    {
        return _alive;
    }
    
    void    AUnit::setAlive(bool status)
    {
        _alive = status;
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
    
    int    AUnit::getX(Timer::time time)
    {
        if (time != _t)
        {
            _tX = move(time).first;
            _tY = move(time).second;
            _t = time;
        }
        return _tX;
    }
    
    int    AUnit::getY(Timer::time time)
    {
        if (time != _t)
        {
            _tX = move(time).first;
            _tY = move(time).second;
            _t = time;
        }
        return _tY;
    }
    
    bool        AUnit::isHitting(AUnit *unit, Timer::time time)
    {
        if ((getMax(getX(time), unit->getX(time)) < getMin(getX(time) + _hitBox.first, unit->getX(time) + unit->getHitBox().first))
            && (getMax(getY(time), unit->getY(time)) < getMin(getY(time) + _hitBox.second, unit->getY(time) + unit->getHitBox().second)))
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
