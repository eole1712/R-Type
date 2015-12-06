#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

# include <list>
# include <map>
# include "AMonster.hpp"

class LibLoader;

typedef Unit::Monster::AMonster*	(*fptrNewMonster)();
typedef void				(*fptrDeleteMonster)(Unit::Monster::AMonster*);

class MonsterFactory
{
public:
  MonsterFactory();
  MonsterFactory(std::map<Unit::Monster::type, std::string>);
  ~MonsterFactory();

  Unit::Monster::AMonster*	createMonster(Unit::Monster::type);

  bool				addMonsterType(Unit::Monster::type, std::string libName);
  bool				removeMonsterType(Unit::Monster::type);

private:
  std::list<std::pair<Unit::Monster::type, LibLoader*> >	_libs;
};

#endif /* !MONSTERFACTORY_HPP_ */
