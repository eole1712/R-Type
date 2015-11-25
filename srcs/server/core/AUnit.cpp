
#include "AUnit.hpp"

namespace Unit {

    AUnit::AUnit(unsigned int hp, team t, unsigned int x, unsigned int y, boxType hitBox)
    : _hp(hp), _team(t), _x(x), _y(y), _hitBox(hitBox)
    {
    }
    
    AUnit::~AUnit()
    {
    }
    
    bool    AUnit::isAlive() const
    {
        return (_hp > 0);
    }
    
    unsigned int    AUnit::getX() const
    {
        return _x;
    }
    
    unsigned int    AUnit::getY() const
    {
        return _y;
    }
    
    void        AUnit::setX(unsigned int x)
    {
        _x = x;
    }
    
    void        AUnit::setY(unsigned int y)
    {
        _y = y;
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
    
    bool        AUnit::isHitting(AUnit *unit) const
    {
        if (((_posX + _hitBox.first) > (unit->getX() - unit->getHitBox().first)
             || (_posX - _hitBox.first) < (unit->getX() + unit->getHitBox().first))
            && ((_posY + _hitBox.second) > (unit->getY() - unit->getHitBox().second)
                || (_posX - _hitBox.second) < (unit->getY() + unit->getHitBox().second)))
            return true;
        return false;
    }
}