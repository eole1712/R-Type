#ifndef AUnit_hpp
#define AUnit_hpp

#include <list>
#include <SFML/Graphics.hpp>
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
    RIGHT,
    LEFT
  };

  enum team {
    ALLY,
    ENEMY
  };

  typedef std::pair<int, int> pos;

  // : public UnitRender
  class AUnit  {

  public:
    AUnit(int x, int y, unsigned int id, Timer::time creationTime);
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
    Timer::time     getCreationTime() const;

  public:
    virtual unsigned int  getID() const;
    virtual void	  render(sf::RenderWindow & window) = 0;

  protected:
    int                                     _x;
    int                                     _y;

  protected:
    unsigned int                            _id;
    Timer::time                             _creationTime;
  };
}

#endif /* AUnit_hpp */
