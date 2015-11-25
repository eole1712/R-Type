#ifndef IMAP_H_
# define IMAP_H_

# include "AUnit.hpp"

class IMap
{
public:
  virtual ~IMap() {}

  virtual std::list<Unit::AUnit*> const	&getList(Unit::team) const = 0;

  virtual void				addUnit(Unit::AUnit*) = 0;
  virtual Unit::AUnit*			checkInterractions(Unit::AUnit*) const = 0;
};

#endif /* !IMAP_H_ */
