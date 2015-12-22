#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include "IMap.hpp"
#include "Map.hpp"
#include "IScore.hpp"
#include "ScoreList.hpp"
#include "AUnit.hpp"
#include "Player.hpp"
#include "Game.hpp"
#include "Timer.hpp"
#include "ObjectCast.hpp"
#include "AMonster.hpp"
#include "GameUtils.hpp"

Game::Game(unsigned int id, std::string name, IGameUnitSender* owl)
: _id(id), _name(name), _map(new Map()), _scores(new ScoreList()), _waveManager(_map, id, owl), _t(0), _inGame(false), _owl(owl), _time(0), _now(0), _refresh(1)
{
}

Game::~Game()
{
    std::for_each(this->_players.begin(), this->_players.end(), [](Unit::Player* player)
                  {
                      if (player != nullptr)
                          delete player;
                  });
    delete this->_scores;
    delete this->_map;
}

unsigned int	Game::getID() const
{
    return (this->_id);
}

Timer::time          Game::getTime() const
{
    return _now;
}

std::string     Game::getName() const
{
    return _name;
}

IMap*	Game::getMap() const
{
    return (this->_map);
}

unsigned int    Game::getNbPlayers() const
{
    unsigned int    nb;
    
    nb = 0;
    for (auto& player: _players)
    {
        if (player->getUser())
            nb++;
    }
    return nb;
}

IScoreList*	Game::getScores() const
{
    std::for_each(_players.begin(), _players.end(), [this](Unit::Player* player)
                  {
                      this->_scores->setScore(player);
                  });
    return (this->_scores);
}

Unit::Player*	Game::getPlayer(Unit::color color) const
{
    std::vector<Unit::Player*>::const_iterator it;
    
    for(it = _players.begin(); it != _players.end(); it++)
    {
        if ((*it)->getColor() == color)
            return (*it);
    }
    return (nullptr);
}

bool    Game::isStarted() const
{
    return _inGame;
}

bool	Game::addPlayer(User* user)
{
    unsigned int	ixPlayer = static_cast<unsigned int>(this->_players.size());
    
    if (_inGame)
        return false;
    for (auto& player : _players)
    {
        if (player->getUser() == nullptr)
        {
            player->setUser(user);
            _users.push_back(user);
            user->startGame(_id, player);
            return true;
        }
    }
    
    if (ixPlayer < 4)
    {
      this->_players.push_back(new Unit::Player(Unit::color(Unit::BLUE + ixPlayer), user, ixPlayer + 1, _id, _now));
      _users.push_back(user);
      return (true);
    }
    return (false);
}

void                Game::removePlayer(Unit::color color)
{
    Unit::Player    *player = nullptr;
    
    for (auto& pl : _players) {
        if (pl->getColor() == color)
            player = pl;
    }

    if (player->getUser())
    {
        player->getUser()->endGame(player->getScore());
        _users.erase(std::remove(_users.begin(), _users.end(), player->getUser()), _users.end());
        player->setUser(nullptr);
    }
}

std::vector<User*> const&     Game::getUsers() const
{
    return _users;
}

void        Game::checkMouvements()
{
    std::list<Unit::AUnit*>::iterator it;
    
    std::for_each(_players.begin(), _players.end(), [this](Unit::Player *player)
                  {
                      if (_t.isFinished())
                          Unit::Player::checkMouvement(player, _map);
                      Unit::AUnit *unit = _map->checkInterractions(player, _now);
                      if (unit) {
                          
                          (player)->getHit(unit);
                          unit->getHit(player);
                      }
                  });
    
    for (it = _map->getList(Unit::ALLY).begin(); it != _map->getList(Unit::ALLY).end(); it++) {
        Unit::AUnit *unit = _map->checkInterractions(*it, _now);
        if (unit) {
            (*it)->getHit(unit);
            unit->getHit(*it);
        }
    }
    
//    for (it = _map->getList(Unit::ENEMY).begin(); it != _map->getList(Unit::ENEMY).end(); it++) {
//        Unit::AUnit *unit = _map->checkInterractions(*it, time);
//        if (unit) {
//            (*it)->getHit(unit);
//            uniit->getHit(*it);
//        }
//    }
    if (_t.isFinished())
    {
        _t.reset(10);
        _t.start();
    }
}

void        Game::shootThemAll()
{
    std::for_each(_players.begin(), _players.end(), [this](Unit::Player *player) {
        if (player->isShooting()) {
            Unit::AUnit* m = player->shoot(_now);
            if (m)
            {
                m->setID(_idc.getNewID());
                _map->addUnit(m);
                _owl->sendUnit(m, m->getTypeID());
            }
        }
    });
    std::for_each(_map->getList(Unit::ENEMY).begin(), _map->getList(Unit::ENEMY).end(), [this](Unit::AUnit* unit){
        if (unit->getType() == Unit::MONSTER) {
            Unit::AUnit* m = ObjectCast::getObject<Unit::Monster::AMonster*>(unit)->shoot(_now);
            if (m)
            {
                m->setID(_idc.getNewID());
                _map->addUnit(m);
                _owl->sendUnit(m, m->getTypeID());
            }
        }
    });
}

bool        Game::checkIfAlive()
{
    int                                 i = 0;
    
    std::for_each(_players.begin(), _players.end(), [&i, this](Unit::Player *player) {
        if (player->isAlive()) {
            if (player->healthCheck(_now) == false) {
                player->setAlive(false);
                _owl->killUnit(player->getID(), _id);
            }
            else {
                i++;
            }
        }
    });
    if (i == 0)
        return false;
    
	auto it = _map->getList(Unit::ALLY).begin();
	while (it != _map->getList(Unit::ALLY).end()) {
		if ((*it)->getType() == Unit::MISSILE && (*it)->healthCheck(_now) == false)
        {
            _owl->killUnit((*it)->getID(), _id);
            it = _map->getList((*it)->getTeam()).erase(it);
        }
        else
			it++;
	}
	it = _map->getList(Unit::ENEMY).begin();
	while (it != _map->getList(Unit::ENEMY).end()) {
		if ((*it)->healthCheck(_now) == false)
        {
            _owl->killUnit((*it)->getID(), _id);
			it = _map->getList((*it)->getTeam()).erase(it);
        }
		else
			it++;
	}
    return true;
}

void        Game::tryToRefresh()
{
    if (_now > (_refresh * 1000))
    {
        _owl->refreshTimer(_id, _now);
        _refresh++;
    }
}

void        Game::start()
{
    _inGame = true;
    _t.start();
    _time.start();
    for (auto& player : _players)
    {
        player->setX(30);
        player->setY(player->getID() * (GameUtils::Map::HEIGHT / (_players.size() + 1)));
        if (!player->getUser())
            player->setAlive(false);
        else
            _owl->sendUnit(player, Unit::PLAYERTYPE);
    }
}

bool        Game::end()
{
    std::vector<User*> users = getUsers();
    std::for_each(_players.begin(), _players.end(), [](Unit::Player *player){
        if (player->getUser())
			player->getUser()->endGame(player->getScore());
    });
    return false;
}

bool        Game::nextAction()
{
    _now = _time.getElapsedTime();
    _waveManager.execConfig(_now);
    checkMouvements();
    shootThemAll();
    _waveManager.nextAction(_now, &_idc);
    if (checkIfAlive() == false)
        return end();
    tryToRefresh();
    return true;
}
