#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

# include <list>
# include "IMonster.hpp"
# include "LibLoader.hpp"

# typedef IMonster*	(*fptrNewMonster)();
# typedef void		(*fptrDeleteMonster)(IMonster*);

class MonsterFactory
{
public:
  MonsterFactory();
  MonsterFactory(std::map<Monster::type, std::string libName>);
  ~MonsterFactory();

  IMonster*	createMonster(Monster::type);

  bool		addMonsterType(Monster::type, std::string libName);
  bool		removeMonsterType(Monster::type);

private:
  std::list<std::pair<Monster::type, LibLoader*> >	_libs;
};

#endif /* !MONSTERFACTORY_HPP_ */
