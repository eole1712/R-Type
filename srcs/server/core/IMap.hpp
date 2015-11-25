#ifndef IMAP_H_
# define IMAP_H_

# include "AUnit.hpp"

class IMap
{
public:
  IMap();
  virtual ~IMap() {}

  virtual std::list<Unit::AUnit*>	getList(Unit::team) const = 0;

  virtual void				addUnit(Unit::AUnit*) = 0;
  virtual Unit::AUnit*			checkInterractions(Unit::AUnit*) const = 0;
};

#endif /* !IMAP_H_ */
