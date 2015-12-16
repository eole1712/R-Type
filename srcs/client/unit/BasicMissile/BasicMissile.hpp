#ifndef BASICMISSILE_H_
# define BASICMISSILE_H_

# include "AUnit.hpp"
# include "Animation.hpp"

namespace Unit
{
  class BasicMissile : public AUnit
  {
  public:
    BasicMissile(int x, int y, unsigned int id, Time::stamp creationTime);
    virtual ~BasicMissile();
    
    virtual pos	move(Time::stamp) const;
    virtual void	render(Time::stamp tick, sf::RenderWindow & window);
    
  private:
    Animation	_mySprite;
  };
}

#endif /* !BASICMISSILE_H_ */
