#include "Timer.hpp"
#include "AUnit.hpp"
#include "Game.hpp"

namespace Unit {

  AUnit::AUnit(unsigned int hp, team t, int x, int y, boxType hitBox, unsigned int id, unsigned int gameID)
  : _hp(hp), _team(t), _x(x), _y(y), _hitBox(hitBox), _id(id), _gameID(gameID), _creationTime(Game::now(gameID))
  {
  }

  AUnit::~AUnit()
  {
  }

  bool    AUnit::isAlive() const
  {
    return (_hp > 0);
  }

  boxType     AUnit::getHitBox() const
  {
    return _hitBox;
  }

  void        AUnit::setHitBox(boxType hitBox)
  {
    _hitBox = hitBox;
  }

  team        AUnit::getTeam() const
  {
    return _team;
  }

  void        AUnit::setTeam(team t)
  {
    _team = t;
  }
  
  unsigned int  AUnit::getID() const
  {
    return _id;
  }
  
  unsigned int  AUnit::getGameID() const
  {
    return _gameID;
  }

  Timer::time AUnit::getCreationTime() const
  {
    return _creationTime;
  }
  
  int    AUnit::getX() const
  {
    return move().first;
  }
  
  int    AUnit::getY() const
  {
    return move().second;
  }
  
  bool        AUnit::isHitting(AUnit *unit) const
  {
    if ((((getX() + _hitBox.first) > (unit->getX() - unit->getHitBox().first))
	 || ((getX() - _hitBox.first) < (unit->getX() + unit->getHitBox().first)))
	&& (((getY() + _hitBox.second) > (unit->getY() - unit->getHitBox().second))
	    || ((getY() - _hitBox.second) < (unit->getY() + unit->getHitBox().second))))
      return true;
    return false;
  }
}
