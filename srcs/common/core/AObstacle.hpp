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
  AObstacle(unsigned int x, unsigned int y, Unit::boxType hitbox);
  virtual ~AObstacle();

  virtual Unit::type		getType() const;
  virtual Obstacle::type	getBonusType() const = 0;
};

}

}

#endif /* !AOBSTACLE_H_ */
