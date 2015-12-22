#ifndef DIRECTEDMISSILE_H_
# define DIRECTEDMISSILE_H_

# include "AUnit.hpp"
# include "Animation.hpp"
# include "SoundPlayer.hpp"

namespace Unit
{
  class DirectedMissile : public AUnit
  {
  public:
    DirectedMissile(int x, int y, unsigned int id, Time::stamp creationTime, float param);
    virtual ~DirectedMissile();
    
    virtual pos		move(Time::stamp) const;
    virtual void	render(Time::stamp tick, sf::RenderWindow & window);
    virtual typeID	getType() const;
    
  private:
    Animation	_mySprite;
    SoundPlayer*_mySound;
  };
}

#endif /* !DIRECTEDMISSILE_H_ */
