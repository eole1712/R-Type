#include <string>
#include <vector>
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

Game::Game(unsigned int id, std::string name)
: _id(id), _name(name), _map(new Map()), _scores(new ScoreList()), _players(4, nullptr), _waveManager(_map, id), _t(0)
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

std::string     Game::getName() const
{
    return _name;
}

IMap*	Game::getMap() const
{
    return (this->_map);
}

unsigned long    Game::getNbPlayers() const
{
    return _players.size();
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

bool	Game::addPlayer(std::string name)
{
    unsigned int	ixPlayer = static_cast<unsigned int>(this->_players.size());
    
    if (ixPlayer < 4)
    {
        this->_players[ixPlayer] = new Unit::Player(Unit::color(Unit::BLUE + ixPlayer), name,ixPlayer + 1, _id);
        return (true);
    }
    return (false);
}

void	Game::removePlayer(Unit::color color)
{
    unsigned int	i = 0;
    
    std::for_each(this->_players.begin(), this->_players.end(),
                  [this, color, &i](Unit::Player* player)
                  {
                      if (player->getColor() == color)
                      {
                          delete player;
                          this->_players[i] = nullptr;
                      }
                      ++i;
                  });
}

void        Game::checkMouvements(Timer &t)
{
    std::list<Unit::AUnit*>::iterator it;
    
    std::for_each(_players.begin(), _players.end(), [&t, this](Unit::Player *player)
                  {
                      if (t.isFinished())
                          Unit::Player::checkMouvement(player, _map);
                  });
    
    for (it = _map->getList(Unit::ALLY).begin(); it != _map->getList(Unit::ALLY).end(); it++) {
        Unit::AUnit *unit = _map->checkInterractions(*it);
        if (unit) {
            (*it)->getHit(unit);
            unit->getHit(*it);
        }
    }
    
    for (it = _map->getList(Unit::ENEMY).begin(); it != _map->getList(Unit::ENEMY).end(); it++) {
        Unit::AUnit *unit = _map->checkInterractions(*it);
        if (unit) {
            (*it)->getHit(unit);
            unit->getHit(*it);
        }
    }
    
    t.reset(60);
    t.start();
}

void        Game::shootThemAll()
{
    std::for_each(_players.begin(), _players.end(), [](Unit::Player *player) {
        if (player->isShooting())
            player->shoot();
    });
    std::for_each(_map->getList(Unit::ENEMY).begin(), _map->getList(Unit::ENEMY).end(), [](Unit::AUnit* unit){
        if (unit->getType() == Unit::MONSTER) {
            ObjectCast::getObject<Unit::Monster::AMonster*>(unit)->shoot();
        }
    });
}

bool        Game::checkIfAlive()
{
    int     i = 0;
    std::list<Unit::AUnit*>::iterator it;
    
    std::for_each(_players.begin(), _players.end(), [&i](Unit::Player *player) {
        if (player->isAlive())
            i++;
    });
    if (i == 0)
        return false;
    
    
    for (it = _map->getList(Unit::ALLY).begin(); it != _map->getList(Unit::ALLY).end(); it++) {
        if ((*it)->getType() == Unit::MISSILE && (*it)->isAlive() == false)
            _map->removeUnit(*it);
    }
    for (it = _map->getList(Unit::ENEMY).begin(); it != _map->getList(Unit::ENEMY).end(); it++) {
        if (((*it)->getType() == Unit::MISSILE || (*it)->getType() == Unit::MONSTER) && (*it)->isAlive() == false)
            _map->removeUnit(*it);
    }
    return true;
}

void        Game::start()
{
    _t.start();
}

bool        Game::nextAction()
{
    if (checkIfAlive() == false)
        return false;
    _waveManager.execConfig(_t);
    checkMouvements(_t);
    shootThemAll();
    _waveManager.nextAction();
    return checkIfAlive();
}

unsigned int             Game::getNewID(unsigned int gameID)
{
    static std::map<unsigned int, unsigned int>   tab;
    std::map<unsigned int, unsigned int>::iterator it;
    
    it = tab.find(gameID);
    if (it == tab.end())
        tab[gameID] = 5;
    else
        tab[gameID]++;
    return tab[gameID];
}

Timer::time             Game::now(unsigned int gameID)
{
    static std::map<unsigned int, Timer*>   tab;
    std::map<unsigned int, Timer*>::iterator it;
    
    it = tab.find(gameID);
    if (it == tab.end())
    {
        tab[gameID] = new Timer(0);
    }
    return tab[gameID]->getElapsedTime();
}