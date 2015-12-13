#ifndef AUnit_hpp
#define AUnit_hpp

#include <list>
#include "Timer.hpp"

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
  
  class AUnit {
    
  public:
    AUnit(unsigned int hp, team, int x, int y, boxType hitBox, unsigned int id, unsigned int gameID);
    virtual ~AUnit();
  private:
    AUnit(AUnit const &);
    AUnit &operator=(AUnit const &);
    
  public:
    virtual bool    isAlive() const;
    virtual void    getHit(AUnit*) = 0;
    
  public:
    virtual int     getX() const;
    virtual int     getY() const;
      
  public:
    virtual pos     move() const = 0;
    
  public:
    virtual boxType getHitBox() const;
    virtual void    setHitBox(boxType);
    
  public:
    virtual bool    isHitting(AUnit*) const;
    
  public:
    virtual type    getType() const = 0;
    
  public:
    virtual team    getTeam() const;
    virtual void    setTeam(team t);
    
  public:
    Timer::time     getCreationTime() const;
    
  public:
    virtual unsigned int  getID() const;
    virtual unsigned int  getGameID() const;
    
  protected:
    unsigned int                            _hp;
    team                                    _team;
    
  protected:
    int                                     _x;
    int                                     _y;
    
  protected:
    boxType                                 _hitBox;
    unsigned int                            _id;
    unsigned int                            _gameID;
    Timer::time                             _creationTime;
  };
}

#endif /* AUnit_hpp */
