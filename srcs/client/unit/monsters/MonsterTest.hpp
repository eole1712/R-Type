#ifndef MONSTERTEST_H_
# define MONSTERTEST_H_

# include "AUnit.hpp"
# include "Animation.hpp"
# include "Time.hpp"

namespace Unit
{

class MonsterTest : public AUnit
{
public:
  MonsterTest(int x, int y, unsigned int id, Time::stamp creationTime);
  virtual ~MonsterTest();

  virtual pos	move(Time::stamp tick) const;
  virtual void	render(Time::stamp tick, sf::RenderWindow& window);

private:
  Animation	_mySprite;
};

}

#endif /* !MONSTERTEST_H_ */
