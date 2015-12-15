#ifndef AUnit_hpp
#define AUnit_hpp

#include <list>
#include <SFML/Graphics.hpp>
#include "Time.hpp"

namespace Unit {

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

  class AUnit
  {

  public:
    AUnit(int x, int y, unsigned int id, Time::stamp creationTime);
    virtual ~AUnit();

  private:
    AUnit(AUnit const &);
    AUnit &operator=(AUnit const &);

  public:

  
    virtual Time::stamp		getCreationTime() const;
    virtual unsigned int	getID() const;
    virtual int			getX() const;
    virtual int			getY() const;

    virtual pos     move() const = 0;
    virtual void    render(sf::RenderWindow & window) = 0;

  protected:
    int                                     _x;
    int                                     _y;
    unsigned int                            _id;
    Time::stamp                             _creationTime;
  };
}

#endif /* AUnit_hpp */
