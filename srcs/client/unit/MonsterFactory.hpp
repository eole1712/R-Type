#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

# include <map>
# include <list>
# include <string>
# include "AMonster.hpp"

typedef Unit::Monster::AMonster*	(*fptrNewMonster)(int x, int y,
							  unsigned int id, Time::stamp creationTime);
typedef void				(*fptrDeleteMonster)(Unit::Monster::AMonster*);

class ILibLoader;

namespace Monster {

class Factory
{
private:
  Factory();

public:
  ~Factory();

  Unit::Monster::AMonster*	createMonster(Unit::Monster::type, int x, int y,
					      unsigned int id, Time::stamp creationTime);

  bool				addMonsterType(Unit::Monster::type, std::string libName);
  bool				removeMonsterType(Unit::Monster::type);

  static Factory*		getInstance();
  static void			destroy();

  static const std::map<Unit::Monster::type, std::string>	LIBSLIST;

private:
  std::list<std::pair<Unit::Monster::type, ILibLoader*> >	_libs;

  static Factory*						_instance;
};

}

#endif /* !MONSTERFACTORY_HPP_ */
