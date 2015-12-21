#ifndef BIGHUNTER_H_
# define BIGHUNTER_H_

# include "AUnit.hpp"
# include "Animation.hpp"

namespace Unit
{
  class BigHunter : public AUnit
  {
  public:
    BigHunter(int x, int y, unsigned int id, Time::stamp creationTime, float param);
    virtual ~BigHunter();
    
    virtual pos	move(Time::stamp) const;
    virtual void	render(Time::stamp tick, sf::RenderWindow & window);
    
  private:
    Animation	_mySprite;
  };
}

#endif /* !MONSTERTEST_H_ */
