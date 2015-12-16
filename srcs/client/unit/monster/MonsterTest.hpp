#ifndef MONSTERTEST_H_
# define MONSTERTEST_H_

# include "AMonster.hpp"
# include "AUnit.hpp"
# include "Animation.hpp"

namespace Unit
{

  namespace Monster
  {

    class MonsterTest : public AMonster
    {
    public:
      MonsterTest(int x, int y, unsigned int id, Time::stamp creationTime);
      virtual ~MonsterTest();

      virtual void	render(sf::RenderWindow & window);
      virtual pos	move(Time::stamp) const;
      virtual void	render(Time::stamp tick, sf::RenderWindow & window);

    private:
      Animation		_mySprite;
    };

  }

}

#endif /* !MONSTERTEST_H_ */
