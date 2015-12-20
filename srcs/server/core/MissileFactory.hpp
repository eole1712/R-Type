#ifndef MISSILEFACTORY_H_
# define MISSILEFACTORY_H_

# include <string>
# include <map>
# include <list>
# include "AMissile.hpp"

typedef Unit::Missile::AMissile*	(*fptrNewMissile)(Unit::AUnit* origin, unsigned int id, Timer::time);
typedef void				(*fptrDeleteMissile)(Unit::Missile::AMissile*);

class ILibLoader;

namespace Unit
{

namespace Missile
{

class Factory
{
private:
  Factory();

public:
  ~Factory();

public:
    Unit::Missile::AMissile*	createMissile(Unit::Missile::type type, Unit::AUnit* origin, unsigned int id, Timer::time);

  bool				addMissileType(Unit::Missile::type, std::string libName);
  bool				removeMissileType(Unit::Missile::type);

  static Factory*		getInstance();
  static void			destroy();

  static const std::map<Unit::Missile::type, std::string>	LIBSLIST;

private:
  std::list<std::pair<Unit::Missile::type, ILibLoader*> >	_libs;

  static Factory*						_instance;
};

}

}


#endif /* !MISSILEFACTORY_H_ */
