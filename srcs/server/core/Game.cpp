#include <string>
#include <vector>
#include <algorithm>
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

Game::Game(unsigned int id)
  : _id(id), _players(4, nullptr)
{
  this->_map = new Map();
  this->_scores = new ScoreList();
  this->_monsterFactory = new MonsterFactory();
}

Game::~Game()
{
  std::for_each(this->_players.begin(), this->_players.end(), [](Unit::Player* player)
  {
    if (player != nullptr)
      delete player;
  });
  delete this->_monsterFactory;
  delete this->_scores;
  delete this->_map;
}

unsigned int	Game::getID() const
{
  return (this->_id);
}

IMap*	Game::getMap() const
{
  return (this->_map);
}

IScoreList*	Game::getScores() const
{
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

MonsterFactory*	Game::getMonsterFactory() const
{
  return (this->_monsterFactory);
}

bool	Game::addPlayer(std::string name)
{
  unsigned long	ixPlayer = this->_players.size();

  if (ixPlayer < 4)
    {
      this->_players[ixPlayer] = new Unit::Player(Unit::color(Unit::BLUE + ixPlayer), name);
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
    
    for (it = _map->getList(Unit::ALLY).begin(); it != _map->getList(Unit::ALLY).end(); it++) {
        switch ((*it)->getType()) {
            case Unit::PLAYER:
                Unit::Player::checkMouvement(*it, _map);
                break;
            case Unit::MISSILE:
                ObjectCast::getObject<Unit::Missile::AMissile*>(*it)->move();
            default:
                break;
        }
    }
    
    for (it = _map->getList(Unit::ENEMY).begin(); it != _map->getList(Unit::ENEMY).end(); it++) {
        switch ((*it)->getType()) {
            case Unit::MONSTER:
                ObjectCast::getObject<Unit::Monster::AMonster*>(*it)->move();
            case Unit::MISSILE:
                ObjectCast::getObject<Unit::Missile::AMissile*>(*it)->move();
            default:
                break;
        }
    }
    
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

void        Game::start()
{
    Timer    t(0);
  
    while (_players.size() > 0)
    {
        if (t.isFinished())
            checkMouvements(t);
        shootThemAll();
    }
}