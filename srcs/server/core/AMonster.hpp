#ifndef AMONSTER_H_
# define AMONSTER_H_

# include "AUnit.hpp"
# include "AMissile.hpp"

namespace Monster
{

enum type {
  MONSTER1,
  MONSTER2
};

class AMonster : public AUnit
{
public:
  AMonster();
  virtual ~AMonster() {}

  Unit::type	getType() const;
  Monster::type	getMonsterType() const = 0;

  AMissile*	shoot() const = 0;
  bool		move() = 0;

protected:
  Missile::type	_weapon;
};

}

#endif /* !AMONSTER_H_ */
