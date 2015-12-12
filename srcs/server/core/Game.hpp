#ifndef GAME_H_
# define GAME_H_

# include <string>
# include <vector>
# include "IGame.hpp"
# include "AUnit.hpp"
# include "Player.hpp"
# include "MonsterFactory.hpp"

class IMap;
class IScoreList;

class Game : public IGame
{
public:
    Game(unsigned int id);
    virtual ~Game();
    
    virtual unsigned int		getID() const;
    virtual IMap*			getMap() const;
    virtual IScoreList*		getScores() const;
    virtual Unit::Player*		getPlayer(Unit::color) const;
    virtual MonsterFactory*	getMonsterFactory() const;
    
    virtual bool			addPlayer(std::string name);
    virtual void			removePlayer(Unit::color);
    virtual void        start();
    virtual void        checkMouvements(Timer &);
    virtual void        shootThemAll();
    virtual bool        checkIfAlive();
    
public:
    static unsigned int     getNewID(unsigned int id);
    static Timer::time      now(unsigned int id);
    
private:
    unsigned int			_id;
    IMap*				_map;
    IScoreList*			_scores;
    std::vector<Unit::Player*>	_players;
    MonsterFactory*		_monsterFactory;
};

#endif /* !GAME_H_ */
