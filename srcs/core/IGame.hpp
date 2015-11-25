#ifndef IGAME_H_
# define IGAME_H_

# include <string>
# include "AUnit.hpp"

class IMap;
class IScore;

class IGame
{
public:
  IGame();
  virtual ~IGame() {}

  virtual unsigned int	getID() const = 0;
  virtual IMap*		getMap() const = 0;
  virtual IScore*	getScores() const = 0;

  virtual AUnit::Color	addPlayer(std::string name) = 0;
  virtual bool		removePlayer(AUnit::Color) = 0;
};

#endif /* !IGAME_H_ */
