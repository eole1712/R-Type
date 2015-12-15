#include "User.hpp"
#include "Player.hpp"

User::User(std::string const &name, unsigned int clientID)
: _clientID(clientID), _name(name), _gameID(0), _player(nullptr), _score(0)
{
}

User::~User()
{
}

unsigned int      User::getClientID() const
{
    return _clientID;
}

std::string       User::getName() const
{
    return _name;
}

Unit::Player*     User::getPlayer() const
{
    return _player;
}

unsigned int      User::getGameID() const
{
    return _gameID;
}

void              User::startGame(unsigned int gameID, Unit::Player *player)
{
    if (_gameID == 0)
    {
        _gameID = gameID;
        _player = player;
    }
}

void              User::endGame(unsigned int score)
{
    if (_gameID > 0)
    {
        _score += score;
        _gameID = 0;
        _player = nullptr;
    }
}

bool            User::isInGame() const
{
    return (_gameID != 0);
}

unsigned int    User::getScore() const
{
    return _score;
}

bool            User::isReady() const
{
    return _ready;
}

void            User::setReady(bool ready)
{
    _ready = ready;
}