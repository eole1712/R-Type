#ifndef ISCORELIST_H_
# define ISCORELIST_H_

# include "AUnit.hpp"

class Player;
class IScore;

class IScoreList
{
public:
  IScoreList();
  virtual ~IScoreList() {}

  virtual IScore*	getScore(Unit::color) const = 0;
  virtual void		setScore(Player*) = 0;
};

#endif /* !ISCORELIST_H_ */
