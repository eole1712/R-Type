#ifndef AMONSTER_H_
# define AMONSTER_H_

# include "AUnit.hpp"
# include "AMissile.hpp"

namespace Unit
{

namespace Monster
{

enum type {
  MONSTER1,
  MONSTER2
};

class AMonster : public AUnit
{
public:
  AMonster(unsigned int hp, unsigned int x, unsigned int y, boxType hitBox, Missile::type weapon);
  virtual ~AMonster();

  virtual Unit::type		getType() const;
  virtual Monster::type		getMonsterType() const = 0;

  virtual Missile::AMissile*	shoot() const = 0;
  virtual bool			move() = 0;

protected:
  Missile::type	_weapon;
};

}

}

#endif /* !AMONSTER_H_ */
