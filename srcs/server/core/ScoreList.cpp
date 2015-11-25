#include <algorithm>
#include "IScore.hpp"
#include "Score.hpp"
#include "Player.hpp"
#include "ScoreList.hpp"

ScoreList::ScoreList()
{}

ScoreList::~ScoreList()
{
  std::for_each(this->_scores.begin(), this->_scores.end(), [](IScore* score)
  {
    if (score != nullptr)
      delete score;
  });
}

IScore*	ScoreList::getScore(Unit::color color) const
{
  return (this->_scores[static_cast<unsigned int>(color)]);
}

void	ScoreList::setScore(Unit::Player* player)
{
    IScore*	score = this->_scores[static_cast<unsigned int>(player->getTeam())];

  if (score == nullptr)
    this->_scores[static_cast<unsigned int>(player->getTeam())] = new Score(player->getName(),
									    player->getScore());
  else
    {
      score->setName(player->getName());
      score->setScore(player->getScore());
    }
}
