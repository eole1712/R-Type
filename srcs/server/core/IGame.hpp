#ifndef IGAME_H_
# define IGAME_H_

# include <string>
# include "AUnit.hpp"
# include "IMap.hpp"
# include "Player.hpp"
# include "User.hpp"

class IScoreList;
class MonsterFactory;

class IGame
{
public:
    virtual ~IGame() {}
    
    virtual unsigned int		getID() const = 0;
    virtual IMap*			getMap() const = 0;
    virtual IScoreList*		getScores() const = 0;
    virtual Unit::Player*		getPlayer(Unit::color) const = 0;
    virtual std::string                 getName() const = 0;
    virtual std::vector<User*>          getUsers() const = 0;
    
public:
    virtual void        start() = 0;
    virtual bool        nextAction() = 0;
    
public:
    virtual bool			addPlayer(User*) = 0;
    virtual void			removePlayer(Unit::color) = 0;
    virtual unsigned long   getNbPlayers() const = 0;
};

#endif /* !IGAME_H_ */
