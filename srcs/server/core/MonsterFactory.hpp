#ifndef MONSTERFACTORY_HPP_
# define MONSTERFACTORY_HPP_

# include <list>
# include <map>
# include "AMonster.hpp"

typedef Unit::Monster::AMonster*	(*fptrNewMonster)(int x, int y, unsigned int id, unsigned int gameID);
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

        Unit::Monster::AMonster*	createMonster(Unit::Monster::type, int x, int y, unsigned int gameID);

        bool				addMonsterType(Unit::Monster::type, std::string libName);
        bool				removeMonsterType(Unit::Monster::type);

    private:
        std::list<std::pair<Unit::Monster::type, ILibLoader*> >	_libs;

    public:
        static Factory*    getInstance();

    private:
        static Factory*     _instance;
    };
}

#endif /* !MONSTERFACTORY_HPP_ */
