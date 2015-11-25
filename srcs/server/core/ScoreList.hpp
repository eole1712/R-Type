#ifndef SCORELIST_H_
# define SCORELIST_H_

# include <vector>

# include "AUnit.hpp"
# include "IScoreList.hpp"
# include "Player.hpp"
# include "IScore.hpp"

class ScoreList : public IScoreList
{
public:
  ScoreList();
  virtual ~ScoreList();

  virtual IScore*	getScore(Unit::color) const;
  virtual void		setScore(Unit::Player*);

private:
  std::vector<IScore*>	_scores;
};

#endif /* !SCORELIST_H_ */
