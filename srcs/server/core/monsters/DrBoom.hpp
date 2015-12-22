#ifndef DRBOOM_H_
# define DRBOOM_H_

# include "AUnit.hpp"
# include "AMissile.hpp"

namespace Unit
{

  namespace Monster
  {

    class DrBoom : public AMonster
    {
    public:
      DrBoom(int x, int y, unsigned int id, unsigned int gameID, Timer::time);
      virtual ~DrBoom();

      virtual Monster::type   getMonsterType() const;
      virtual Unit::typeID    getTypeID() const;

      virtual Missile::AMissile*	shoot(Timer::time time);
      virtual pos     move(Timer::time) const;
      virtual void    getHit(AUnit*);
    };
  }
}

#endif /* !DRBOOM_H_ */
