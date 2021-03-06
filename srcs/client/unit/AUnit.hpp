#ifndef AUnit_hpp
#define AUnit_hpp

#include <list>
#include <SFML/Graphics.hpp>
#include "Time.hpp"
#include "UnitType.hpp"

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
    AUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param);
    virtual ~AUnit();

  private:
    AUnit(AUnit const &);
    AUnit &operator=(AUnit const &);

  public:


    virtual Time::stamp		getCreationTime() const;
    virtual unsigned int	getID() const;

    virtual pos			move(Time::stamp tick) const;
    virtual void		render(Time::stamp tick, sf::RenderWindow & window) = 0;
    virtual typeID		getType() const = 0;
  
  protected:
    int                                     _x;
    int                                     _y;
    int                                     _trueX;
    int                                     _trueY;
    unsigned int                            _id;
    float				    _param;
    Time::stamp                             _creationTime;
  };
}

#endif /* AUnit_hpp */
