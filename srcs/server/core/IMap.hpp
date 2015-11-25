#ifndef IMAP_H_
# define IMAP_H_

# include "AUnit.hpp"

class IMap
{
public:
  IMap();
  virtual ~IMap() {}

  virtual std::list<AUnit*>	getList(Unit::team) const = 0;
  virtual void			addUnit(AUnit*) = 0;
  virtual AUnit*		checkInterractions(AUnit*) const = 0;
};

#endif /* !IMAP_H_ */
