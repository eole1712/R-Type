#include "MonsterLabel.hpp"

namespace Monster {
  
  Label::Label(Unit::Monster::type type, int x, int y, Timer::time time)
  : _x(x), _y(y), _type(type), _time(time)
  {
  }
  
  Label::Label(Label const &unit)
  : _x(unit.getX()), _y(unit.getY()), _type(unit.getType()), _time(unit.getTime())
  {
  }
  
  Label::~Label()
  {
  }
  
  int         Label::getX() const
  {
    return _x;
  }
  
  int         Label::getY() const
  {
    return _y;
  }
  
  Unit::Monster::type   Label::getType() const
  {
    return _type;
  }
  
  Timer::time           Label::getTime() const
  {
    return _time;
  }
  
}