#include <string>
#include "Score.hpp"

Score::Score(std::string name, unsigned int score)
  : _name(name), _score(score)
{}

Score::~Score()
{}

std::string	Score::getName() const
{
  return (this->_name);
}

unsigned int	Score::getScore() const
{
  return (this->_score);
}

void	Score::setName(std::string name)
{
  this->_name = name;
}

void	Score::setScore(unsigned int score)
{
  this->_score = score;
}
