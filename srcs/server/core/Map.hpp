#ifndef MAP_H_
# define MAP_H_

# include <list>
# include "AUnit.hpp"
# include "IMap.hpp"

class Map
{
public:
  Map();
  virtual ~Map();

  virtual std::list<Unit::AUnit*> const&	getList(Unit::team) const;

  virtual void					addUnit(Unit::AUnit*);
  virtual Unit::AUnit*				checkInterractions(Unit::AUnit*) const;

private:
  std::list<AUnit*>	_allies;
  std::list<AUnit*>	_ennemies;
};

#endif /* !MAP_H_ */
