#ifndef AMONSTER_H_
# define AMONSTER_H_

# include "AUnit.hpp"
# include "AMissile.hpp"
# include "Timer.hpp"

namespace Unit
{

namespace Monster
{

enum type {
  MONSTERTEST
};

class AMonster : public AUnit
{
public:
  AMonster(unsigned int hp, unsigned int x, unsigned int y, boxType hitBox, Missile::type weapon, dir, unsigned int id, unsigned int gameID);
  virtual ~AMonster();

  virtual Unit::type		getType() const;
  virtual Monster::type		getMonsterType() const = 0;

  virtual Missile::AMissile*	shoot();
  virtual bool			move() = 0;

protected:
  Missile::type     _weapon;
  Timer             _time;
};

}

}

#endif /* !AMONSTER_H_ */
