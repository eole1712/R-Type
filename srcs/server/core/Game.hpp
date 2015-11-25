#ifndef GAME_H_
# define GAME_H_

# include <string>
# include <vector>
# include "AUnit.hpp"
# include "IGame.hpp"
# include "IScoreList.hpp"
# include "Player.hpp"
# include "IMap.hpp"

class Game : public IGame
{
public:
  Game(unsigned int id);
  virtual ~Game();
  
  virtual unsigned int      getID() const;
  virtual IMap*             getMap() const;
  virtual IScoreList*       getScores() const;
  virtual Unit::Player*     getPlayer(Unit::color) const;
  
  virtual bool		addPlayer(std::string name);
  virtual bool		removePlayer(Unit::color);
  
private:
  unsigned int                _id;
  IMap*                       _map;
  IScoreList*                 _scores;
  std::vector<Unit::Player*>	_players;
};

#endif /* !GAME_H_ */
