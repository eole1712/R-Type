#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

# include <list>
# include <map>
# include "AMonster.hpp"
# include "Time.hpp"

typedef Unit::Monster::AMonster*	(*fptrNewMonster)(int x, int y, unsigned int id,
							  Time::stamp creationTime);
typedef void				(*fptrDeleteMonster)(Unit::Monster::AMonster*);

class ILibLoader;

namespace Monster {

class Factory
{
private:
  Factory();
  Factory(std::map<Unit::Monster::type, std::string>);

public:
  ~Factory();

  Unit::Monster::AMonster*	createMonster(Unit::Monster::type, int x, int y,
					      unsigned int id, Time::stamp creationTime);

  bool				addMonsterType(Unit::Monster::type, std::string libName);
  bool				removeMonsterType(Unit::Monster::type);

  static Factory*		getInstance();
  static void			destroy();

private:
  std::list<std::pair<Unit::Monster::type, ILibLoader*> >	_libs;

  static Factory*						_instance;
};

}

#endif /* !MONSTERFACTORY_HPP_ */
