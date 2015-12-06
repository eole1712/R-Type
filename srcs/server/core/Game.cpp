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

bool	Game::removePlayer(Unit::color color)
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
  return (nullptr);
}
