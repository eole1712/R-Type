#ifndef IGAME_H_
# define IGAME_H_

# include <string>
# include "AUnit.hpp"
# include "IMap.hpp"

class IScoreList;
class Player;
class MonsterFactory;

class IGame
{
public:
  virtual ~IGame() {}

  virtual unsigned int		getID() const = 0;
  virtual IMap*			getMap() const = 0;
  virtual IScoreList*		getScores() const = 0;
  virtual Unit::Player*		getPlayer(Unit::color) const = 0;
  virtual MonsterFactory*	getMonsterFactory() const = 0;

  virtual bool			addPlayer(std::string name) = 0;
  virtual bool			removePlayer(Unit::color) = 0;
};

#endif /* !IGAME_H_ */
