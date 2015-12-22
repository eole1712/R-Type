#ifndef WAVEMISSILE_H_
# define WAVEMISSILE_H_

# include "AUnit.hpp"
# include "Animation.hpp"
# include "SoundPlayer.hpp"

namespace Unit
{
  class WaveMissile : public AUnit
  {
  public:
    WaveMissile(int x, int y, unsigned int id, Time::stamp creationTime, float param);
    virtual ~WaveMissile();
    
    virtual pos		move(Time::stamp) const;
    virtual void	render(Time::stamp tick, sf::RenderWindow & window);
    virtual typeID	getType() const;
    
  private:
    Animation	_mySprite;
    SoundPlayer*_mySound;
  };
}

#endif /* !WAVEMISSILE_H_ */
