#ifndef Player_hpp
#define Player_hpp


#include "AUnit.hpp"

#include <string>

namespace Unit {
    
class Player : public AUnit {

public:
    Player(color, std::string name);
    virtual ~Player();

public:
    static const unsigned int               defaultHP;
    static const unsigned Missile::type     defaultMissile;
    static const unsigned int               startX;
    static const unsigned int               startY;
    static const boxType                    defaultHitBox;
    
public:
    Missile::AMissile*      shoot();
    Missile::type           getWeapon();
    void                    setWeapon(Missile::type);
    
public:
    unsigned int    getScore() const;
    void            incScore(unsigned int);

public:
    std::string     getName() const;
    color           getColor() const;
    
public:
    bool            move(dir);

public:
    type            getType() const;
    
private:
    color           _color;
    std::string     _name;
    unsigned int    _score;
    Missile::type   _weapon;
};

}
    
#endif /* Player_hpp */
