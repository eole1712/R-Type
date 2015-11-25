#ifndef SCORELIST_H_
# define SCORELIST_H_

# include "AUnit.hpp"
# include "IScoreList.hpp"

class Player;
class IScore;

class ScoreList
{
public:
  ScoreList();
  virtual ~ScoreList();

  virtual IScore*	getScore(Unit::color) const;
  virtual void		setScore(Player*);

private:
  std::vector<IScore*>	_scores;
};

#endif /* !SCORELIST_H_ */
