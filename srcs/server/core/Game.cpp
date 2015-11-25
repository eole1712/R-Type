#include <string>
#include <vector>
#include <algorithm>
#include "IMap.hpp"
#include "Map.hpp"
#include "IScore.hpp"
#include "Score.hpp"
#include "AUnit.hpp"
#include "Player.hpp"
#include "Game.hpp"

Game::Game(unsigned int id)
  : _id(id), _players(4, nullptr)
{
  this->_map = new Map();
  this->_scores = new Score();
}

Game::~Game()
{
  std::for_each(this->_players.begin(), this->_players.end(), [color](Player* player)
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

IMap*	Game::getMap() const
{
  return (this->_map);
}

IScore*	Game::getScores() const
{
  return (this->_scores);
}

Player*	Game::getPlayer(AUnit::color color) const
{
  std::for_each(this->_players.begin(), this->_players.end(), [color](Player* player)
  {
    if (player->getColor() == color)
      return (player);
  });
  return (nullptr);
}

bool	Game::addPlayer(std::string name)
{
  unsigned int	ixPlayer = this->_players.size();

  if (ixPlayer < 4)
    {
      this->_players[ixPlayer] = new Player(Player::startX, Player::startY, Player::hitBox, AUnit::color::BLUE + ixPlayer, name);
      return (true);
    }
  return (false);
}

bool	Game::removePlayer(AUnit::color color)
{
  unsigned int	i = 0;

  std::for_each(this->_players.begin(), this->_players.end(),
		[this, color, &i](APlayer* player)
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
