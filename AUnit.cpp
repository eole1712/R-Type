
#include "AUnit.hpp"

namespace Unit {

    AUnit::AUnit(unsigned int hp, unsigned int x, unsigned int y, boxType hitBox)
    : _hp(hp), _x(x), _y(y), _hitBox(hitBox)
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
    
    bool        AUnit::isHitting(AUnit *unit) const
    {
        //TODO isHitting
        
        return true;
    }
    
    
}