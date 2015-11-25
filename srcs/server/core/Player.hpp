#ifndef Player_hpp
#define Player_hpp


#include "AUnit.hpp"
#include "AMissile.hpp"

#include <string>

namespace Unit {

class Player : public AUnit {

public:
    Player(color, std::string name);
    virtual ~Player();

public:
    static const unsigned int               defaultHP;
    static const Missile::type              defaultMissile;
    static const unsigned int               startX;
    static const unsigned int               startY;
    static const boxType                    defaultHitBox;
    
public:
    Missile::AMissile*      shoot();
    Missile::type           getWeapon() const;
    void                    setWeapon(Missile::type);
    
public:
    virtual void            getHit(AUnit*);

public:
    unsigned int    getScore() const;
    void            incScore(unsigned int);

public:
    std::string     getName() const;
    color           getColor() const;
    
public:
    bool            move(dir);

public:
    virtual type            getType() const;
    
private:
    color           _color;
    std::string     _name;
    unsigned int    _score;
    Missile::type   _weapon;
};

}
    
#endif /* Player_hpp */
