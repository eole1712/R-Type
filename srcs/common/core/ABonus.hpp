#ifndef ABONUS_H_
# define ABONUS_H_

# include "AUnit.hpp"

namespace Unit
{

namespace Bonus
{

enum type {
  BASIC
};

class ABonus : public AUnit
{
public:
  ABonus(unsigned int x, unsigned int y, Unit::boxType hitbox, unsigned int id);
  virtual ~ABonus();

  virtual void		render(sf::RenderWindow & window);
  virtual Unit::type	getType() const;
  virtual Bonus::type	getBonusType() const = 0;
};

}

}

#endif /* !ABONUS_H_ */
