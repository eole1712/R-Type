#ifndef SCORE_H_
# define SCORE_H_

# include <string>

class Score
{
public:
  Score(std::string name, unsigned int score);
  virtual ~Score();

  virtual std::string	getName() const;
  virtual unsigned int	getScore() const;

  virtual void		setName(std::string);
  virtual void		setScore(unsigned int);

private:
  std::string	_name;
  unsigned int	_score;
};

#endif /* !SCORE_H_ */
