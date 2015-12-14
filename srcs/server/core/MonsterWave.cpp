#include "MonsterWave.hpp"
#include "MonsterFactory.hpp"

namespace Monster {
  
  Wave::Wave(unsigned int gameID)
  : Timer(0), _started(false), _time(0), _list(), _gameID(gameID)
  {
  }
  
  Wave::~Wave()
  {
  }
  
  bool        Wave::addMonster(Unit::Monster::type type, int x, int y)
  {
    if (_started)
      return false;
    _list.push_front(Label(type, x, y, _time));
    return true;
  }
  
  bool        Wave::addWaitingTime(Timer::time time)
  {
    if (_started)
      return false;
    _time = time;
    return true;
  }
  
  bool        Wave::start()
  {
    if (_list.size())
      return false;
    _started = true;
    return true;
  }
  
  Unit::AUnit*      Wave::getNextMonster()
  {
    if (_list.empty())
      return nullptr;
    
    Label    label = _list.front();
    Unit::AUnit*  monster = Monster::Factory::getInstance()->createMonster(label.getType(), label.getX(), label.getY(), _gameID);
    reset(label.getTime());
    return monster;
  }
  
}