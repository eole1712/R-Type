#ifndef IGAME_H_
# define IGAME_H_

# include <string>
# include "AUnit.hpp"

class IMap;
class IScore;
class IPlayer;

class IGame
{
public:
  IGame();
  virtual ~IGame() {}

  virtual unsigned int	getID() const = 0;
  virtual IMap*		getMap() const = 0;
  virtual IScore*	getScores() const = 0;
  virtual IPlayer*	getPlayer(Unit::color) const = 0;

  virtual bool		addPlayer(std::string name) = 0;
  virtual bool		removePlayer(Unit::color) = 0;
};

#endif /* !IGAME_H_ */
