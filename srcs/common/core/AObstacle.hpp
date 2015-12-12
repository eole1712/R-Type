#ifndef AOBSTACLE_H_
# define AOBSTACLE_H_

# include "AUnit.hpp"

namespace Unit
{

namespace Obstacle
{

enum type {
  WALL
};

class AObstacle : public AUnit
{
public:
  AObstacle(unsigned int x, unsigned int y, Unit::boxType hitbox, unsigned int id);
  virtual ~AObstacle();

  virtual void			render(sf::RenderWindow & window);
  virtual Unit::type		getType() const;
  virtual Obstacle::type	getBonusType() const = 0;
};

}

}

#endif /* !AOBSTACLE_H_ */
