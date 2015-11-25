#include <string>
#include "Score.hpp"

Score::Score(std::string name, unsigned int score)
  : _name(name), _score(score)
{}

Score::~Score()
{}

std::string	getName() const
{
  return (this->_name);
}

unsigned int	getScore() const
{
  return (this->_score);
}

void	setName(std::string name)
{
  this->_name = name;
}

void	setScore(unsigned int score)
{
  this->_score = score;
}
