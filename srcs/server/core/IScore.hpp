#ifndef ISCORE_H_
# define ISCORE_H_

# include <string>

class IScore
{
public:
  virtual ~IScore() {}

  virtual std::string	getName() const = 0;
  virtual unsigned int	getScore() const = 0;

  virtual void		setName(std::string) = 0;
  virtual void		setScore(unsigned int) = 0;
};

#endif /* !ISCORE_H_ */
