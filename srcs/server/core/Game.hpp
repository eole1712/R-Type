#ifndef GAME_H_
# define GAME_H_

# include <string>
# include <vector>
# include "IGame.hpp"
# include "AUnit.hpp"
# include "Player.hpp"
# include "MonsterFactory.hpp"
# include "MonsterWaveManager.hpp"
# include "IGameUnitSender.hpp"


class IMap;
class IScoreList;

class Game : public IGame
{
public:
    Game(unsigned int id, std::string name, IGameUnitSender*);
    virtual ~Game();

    virtual unsigned int	getID() const;
    virtual IMap*			getMap() const;
    virtual IScoreList*		getScores() const;
    virtual Unit::Player*	getPlayer(Unit::color) const;
    virtual std::string     getName() const;
    virtual std::vector<User*> const&  getUsers() const;

    virtual bool			addPlayer(User *);
    virtual void			removePlayer(Unit::color);
    virtual unsigned int   getNbPlayers() const;

public:
    virtual void        start();
    virtual bool        nextAction();
    virtual bool        end();
    virtual bool        isStarted() const;

protected:
    virtual void        checkMouvements();
    virtual void        shootThemAll();
    virtual bool        checkIfAlive();

private:
    std::vector<User*>  _users;
    unsigned int		_id;
    std::string         _name;
    IMap*				_map;
    IScoreList*			_scores;
    std::vector<Unit::Player*>	_players;
    Monster::WaveManager    _waveManager;
    Timer               _t;
    bool                _inGame;
    IGameUnitSender*    _owl;
};

#endif /* !GAME_H_ */
