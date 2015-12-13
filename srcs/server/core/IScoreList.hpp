#ifndef ISCORELIST_H_
# define ISCORELIST_H_

# include "AUnit.hpp"
# include "Player.hpp"
# include "IScore.hpp"

class IScoreList
{
public:
  virtual ~IScoreList() {}

  virtual IScore*	getScore(Unit::color) const = 0;
  virtual void		setScore(Unit::Player*) = 0;
};

#endif /* !ISCORELIST_H_ */
