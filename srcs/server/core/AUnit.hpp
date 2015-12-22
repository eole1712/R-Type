#ifndef AUnit_hpp
#define AUnit_hpp

#include <list>
#include "Timer.hpp"
#include "UnitType.hpp"
#include "Lock.hpp"

namespace Unit {
    
    enum type {
        PLAYER,
        MONSTER,
        MISSILE,
        BONUS
    };
    
    enum color : unsigned int {
        BLUE,
        RED,
        YELLOW,
        GREEN
    };
    
    enum dir : int {
        UP,
        DOWN,
        RIGTH,
        LEFT
    };
    
    enum team {
        ALLY,
        ENEMY
    };
    
    typedef std::pair<unsigned int, unsigned int> boxType;
    typedef std::pair<int, int> pos;
    
    constexpr int getMax(int a, int b)
    {
        return a > b ? a : b;
    }
    
    constexpr int getMin(int a, int b)
    {
        return a < b ? a : b;
    }
    
    
    class AUnit {
        
    public:
        AUnit(unsigned int hp, team, int x, int y, boxType hitBox, unsigned int id, unsigned int gameID, Timer::time);
        virtual ~AUnit();
    private:
        AUnit(AUnit const &);
        AUnit &operator=(AUnit const &);
        
    public:
        virtual bool    healthCheck(Timer::time);
        virtual bool    isAlive() const;
        virtual void    setAlive(bool);
        virtual void    getHit(AUnit*) = 0;
        
    public:
        virtual int     getX(Timer::time);
        virtual int     getY(Timer::time);
        
    public:
        virtual int   getStartX() const;
        virtual int   getStartY() const;
        
    public:
        virtual pos     move(Timer::time) const = 0;
        
    public:
        virtual boxType getHitBox() const;
        virtual void    setHitBox(boxType);
        
    public:
        virtual bool    isHitting(AUnit*, Timer::time);
        
    public:
        virtual type    getType() const = 0;
        
    public:
        virtual team    getTeam() const;
        virtual void    setTeam(team t);
        
    public:
        Timer::time     getCreationTime() const;
        
    public:
        virtual unsigned int  getID() const;
        virtual void setID(unsigned int);
        virtual unsigned int  getGameID() const;
        virtual typeID        getTypeID() const = 0;
        
    protected:
        unsigned int                            _hp;
        bool                                    _alive;
        team                                    _team;
        
    protected:
        int                                     _x;
        int                                     _y;
        
    private:
        int                                     _tX;
        int                                     _tY;
        Timer::time                             _t;
        
    protected:
        boxType                                 _hitBox;
        unsigned int                            _id;
        unsigned int                            _gameID;
        Timer::time                             _creationTime;
    };
}

#endif /* AUnit_hpp */
