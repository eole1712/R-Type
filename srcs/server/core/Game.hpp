#ifndef GAME_H_
# define GAME_H_

# include <string>
# include <vector>
# include "AUnit.hpp"
# include "IGame.hpp"

class IMap;
class IScore;
class IPlayer;

class Game
{
public:
  Game();
  virtual ~Game();

  virtual unsigned int	getID() const;
  virtual IMap*		getMap() const;
  virtual IScore*	getScores() const;
  virtual IPlayer*	getPlayer(Unit::color) const;

  virtual bool		addPlayer(std::string name);
  virtual bool		removePlayer(Unit::color);

private:
  unsigned int		_id;
  IMap*			_map;
  IScore*		_scores;
  std::vector<IPlayer*>	_players;
};

#endif /* !GAME_H_ */
