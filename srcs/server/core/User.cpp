#include "User.hpp"

User::User(std::string const &name, unsigned int clientID)
: _clientID(clientID), _name(name), _gameID(0), _player(nullptr), _color(Unit::BLUE), _score(0)
{
}

User::~User()
{
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
        _color = player->getColor();
    }
}

void              User::endGame(ScoreList *list)
{
    if (_gameID > 0)
    {
        _score += list->getScore(_color)->getScore();
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
