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

  typedef std::pair<int, int> pos;

  class AUnit {

  public:
    AUnit(team, int x, int y, unsigned int id, unsigned int gameID, Timer::time creationTime);
    virtual ~AUnit();
  private:
    AUnit(AUnit const &);
    AUnit &operator=(AUnit const &);

  public:
    virtual int     getX() const;
    virtual int     getY() const;

  public:
    virtual pos     move() const = 0;

  public:
    virtual type    getType() const = 0;

  public:
    virtual team    getTeam() const;

  public:
    Timer::time     getCreationTime() const;

  public:
    virtual unsigned int  getID() const;
    virtual unsigned int  getGameID() const;

  protected:
    team                                    _team;

  protected:
    int                                     _x;
    int                                     _y;

  protected:
    unsigned int                            _id;
    unsigned int                            _gameID;
    Timer::time                             _creationTime;
  };
}

#endif /* AUnit_hpp */
