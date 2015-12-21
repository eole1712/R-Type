#ifndef BASICMISSILE_H_
# define BASICMISSILE_H_

# include "AUnit.hpp"
# include "Animation.hpp"
# include "SoundPlayer.hpp"

namespace Unit
{
  class BasicMissile : public AUnit
  {
  public:
    BasicMissile(int x, int y, unsigned int id, Time::stamp creationTime, float param);
    virtual ~BasicMissile();
    
    virtual pos		move(Time::stamp) const;
    virtual void	render(Time::stamp tick, sf::RenderWindow & window);
    virtual typeID	getType() const;
    
  private:
    Animation	_mySprite;
    // SoundPlayer	_mySound;
  };
}

#endif /* !BASICMISSILE_H_ */
