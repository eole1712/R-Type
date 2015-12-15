#ifndef Player_hpp
#define Player_hpp


#include "AUnit.hpp"
#include "AMissile.hpp"
#include "Map.hpp"
#include "Timer.hpp"

#include <string>

namespace Unit {

class Player : public AUnit {

public:
    Player(color, std::string name, unsigned int id, unsigned int gameID);
    virtual ~Player();

public:
    static const unsigned int               DEFAULTHP;
    static const Missile::type              DEFAULTMISSILE;
    static const unsigned int               STARTX;
    static const unsigned int               STARTY;
    static const boxType                    DEFAULTHITBOX;

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
    bool            isMoving(Unit::dir) const;
    bool            isShooting() const;

    void            setMoving(Unit::dir dir, bool isMoving);
    void            setShooting(bool isShooting);
public:
    pos             move() const;
    bool            move(dir, IMap*);

public:
    virtual type    getType() const;

private:
    color           _color;
    std::string     _name;
    unsigned int    _score;
    Missile::type   _weapon;
    Timer           _time;
    
private:
    bool            _isMoving[4];
    bool            _isShooting;
    
public:
    static void     checkMouvement(Player *player, IMap *map);

};

}

#endif /* Player_hpp */
