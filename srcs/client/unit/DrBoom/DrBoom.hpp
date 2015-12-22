#ifndef DRBOOM_H_
# define DRBOOM_H_

# include "AUnit.hpp"
# include "Animation.hpp"

namespace Unit
{
  class DrBoom : public AUnit
  {
  public:
    DrBoom(int x, int y, unsigned int id, Time::stamp creationTime, float param);
    virtual ~DrBoom();
    
    virtual pos	move(Time::stamp) const;
    virtual void	render(Time::stamp tick, sf::RenderWindow & window);
    virtual typeID		getType() const;
    
  private:
    Animation	_mySprite;
  };
}

#endif /* !DRBOOM_H_ */
