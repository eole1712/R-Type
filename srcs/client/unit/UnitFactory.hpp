#ifndef UNITFACTORY_HPP_
# define UNITFACTORY_HPP_

# include <map>
# include <list>
# include <string>
# include "AUnit.hpp"

typedef Unit::AUnit*	(*fptrNewUnit)(int x, int y,
				       unsigned int id, Time::stamp creationTime, float param);
typedef void		(*fptrDeleteUnit)(Unit::AUnit*);

class ILibLoader;

namespace Unit
{

class Factory
{
private:
  Factory();

public:
  ~Factory();

  Unit::AUnit*		createUnit(Unit::typeID, int x, int y,
				   unsigned int id, Time::stamp creationTime, float param);
  void			deleteUnit(AUnit * unit);

  bool			addUnitType(Unit::typeID, std::string libName);
  bool			removeUnitType(Unit::typeID);

  static Factory*	getInstance();
  static void		destroy();

  static const std::map<Unit::typeID, std::string>	LIBSLIST;

private:
  std::list<std::pair<Unit::typeID, ILibLoader*> >	_libs;

  static Factory*					_instance;
};

}

#endif /* !UNITFACTORY_HPP_ */
