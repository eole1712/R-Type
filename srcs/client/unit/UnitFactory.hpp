#ifndef UNITFACTORY_HPP_
# define UNITFACTORY_HPP_

# include <map>
# include <list>
# include <string>
# include "AUnit.hpp"

typedef Unit::AUnit*	(*fptrNewUnit)(int x, int y,
				       unsigned int id, Time::stamp creationTime);
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

  Unit::AUnit*		createUnit(Unit::type, int x, int y,
				   unsigned int id, Time::stamp creationTime);

  bool			addUnitType(Unit::type, std::string libName);
  bool			removeUnitType(Unit::type);

  static Factory*	getInstance();
  static void		destroy();

  static const std::map<Unit::type, std::string>	LIBSLIST;

private:
  std::list<std::pair<Unit::type, ILibLoader*> >	_libs;

  static Factory*					_instance;
};

}

#endif /* !UNITFACTORY_HPP_ */
