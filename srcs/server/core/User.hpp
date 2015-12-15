#ifndef User_hpp
#define User_hpp

#include <stdio.h>
#include <string>

#include "AUnit.hpp"

namespace Unit {
    class Player;
}

class User
{
public:
    User(std::string const &name, unsigned int clientID);
    ~User();
    
public:
    std::string     getName() const;
    unsigned int    getClientID() const;

public:
    Unit::Player*   getPlayer() const;
    unsigned int    getGameID() const;

public:
    void        startGame(unsigned int gameID, Unit::Player *player);
    void        endGame(unsigned int score);
    bool        isInGame() const;
    
public:
    unsigned int    getScore() const;
    
private:
    unsigned int    _clientID;
    std::string     _name;
    
private:
    unsigned int    _gameID;
    Unit::Player*   _player;

private:
    unsigned int    _score;
};

#endif /* User_hpp */
