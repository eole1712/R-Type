#ifndef KAMIKAZPLANE_H_
# define KAMIKAZPLANE_H_
 
# include "AUnit.hpp"
# include "Animation.hpp"

namespace Unit
{
  class KamikazPlane : public AUnit
  {
  public:
    KamikazPlane(int x, int y, unsigned int id, Time::stamp creationTime, float param);
    virtual ~KamikazPlane();
    
    virtual pos	move(Time::stamp) const;
    virtual void	render(Time::stamp tick, sf::RenderWindow & window);
    virtual typeID	getType() const;
      
  private:
    Animation	_mySprite;
  };
}

#endif /* !KAMIKAZPLANE_H_ */
