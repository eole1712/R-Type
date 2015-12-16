#ifndef BasicMissile_hpp
# define BasicMissile_hpp

# include "AUnit.hpp"
# include "Animation.hpp"
# include "Time.hpp"

namespace Unit
{

class BasicMissile : public AUnit
{
public:
  BasicMissile(int x, int y, unsigned int id, Time::stamp creationTime);
  virtual ~BasicMissile();

public:
  virtual pos	move(Time::stamp tick) const;
  virtual void	render(Time::stamp tick, sf::RenderWindow& window);

private:
  Animation	_mySprite;
};

}

#endif /* BasicMissile_hpp */
