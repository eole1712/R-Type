#ifndef Player_hpp
#define Player_hpp


#include "AUnit.hpp"
#include "AMissile.hpp"
#include "Map.hpp"
#include "User.hpp"
#include "Timer.hpp"

#include <mutex>
#include <string>

#include "Lock.hpp"

namespace Unit {

class Player : public AUnit {

public:
    Player(color, User *user, unsigned int id, unsigned int gameID, Timer::time);
    virtual ~Player();

public:
    static const unsigned int               DEFAULTHP;
    static const Missile::type              DEFAULTMISSILE;
    static const unsigned int               STARTX;
    static const unsigned int               STARTY;
    static const boxType                    DEFAULTHITBOX;

public:
    Missile::AMissile*      shoot(Timer::time time);
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
    User*           getUser() const;
    void            setUser(User*);

public:
    bool            isMoving(Unit::dir);
    bool            isShooting();

    void            setMoving(Unit::dir dir, bool isMoving);
    void            setShooting(bool isShooting);
public:
    pos             move(Timer::time) const;
    bool            move(dir, IMap*);

public:
    virtual type            getType() const;
    virtual Unit::typeID    getTypeID() const;

public:
    virtual void    setX(int);
    virtual void    setY(int);
    
private:
    color           _color;
    unsigned int    _score;
    Missile::type   _weapon;
    Timer           _time;
    
private:
    bool            _isMoving[4];
    bool            _isShooting;
    
private:
    User*           _user;

public:
    Lock            _lock;
public:
    static void     checkMouvement(Player *player, IMap *map);

};

}

#endif /* Player_hpp */
