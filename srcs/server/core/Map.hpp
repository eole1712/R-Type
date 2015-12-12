#ifndef MAP_H_
# define MAP_H_

# include <list>
# include "AUnit.hpp"
# include "IMap.hpp"

class Map : public IMap
{
public:
    Map();
    virtual ~Map();
    
    virtual std::list<Unit::AUnit*> &	getList(Unit::team);
    
    virtual void                        addUnit(Unit::AUnit*);
    virtual void                        removeUnit(Unit::AUnit *);
    virtual Unit::AUnit*				checkInterractions(Unit::AUnit*) const;
    
public:
    static const unsigned int	WIDTH;
    static const unsigned int	HEIGHT;
    
private:
    std::list<Unit::AUnit*>	_allies;
    std::list<Unit::AUnit*>	_enemies;
};

#endif /* !MAP_H_ */
