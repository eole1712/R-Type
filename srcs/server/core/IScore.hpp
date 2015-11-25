#ifndef ISCORE_H_
# define ISCORE_H_

# include <string>

class IScore
{
public:
  IScore();
  virtual ~IScore() {}

  virtual std::string	getName() const = 0;
  virtual unsigned int	getScore() const = 0;

  virtual void		setName(std::string) const = 0;
  virtual void		setScore(unsigned int) const = 0;
};

#endif /* !ISCORE_H_ */
