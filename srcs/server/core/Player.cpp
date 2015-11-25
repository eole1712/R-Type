
#include <algorithm>
#include "Player.hpp"
#include "Map.hpp"

namespace Unit {

    const unsigned int          Player::defaultHP = 1;
    const Missile::type         Player::defaultMissile = Missile::BASIC;
    const unsigned int          Player::startX = 10;
    const unsigned int          Player::startX = Map::height / 2;
    const boxType               Player::defaultHitBox = std::make_pair(10, 10);
    
    Player::Player(color c, std::string name)
    : AUnit(defaultHP, ALLY, startX, startY, defaultHitBox), _color(c), _name(name), _score(0), _weapon(defaultMissile)
    {
    }
    
    Player::~Player()
    {
    }
    
    Missile::AMissile*          shoot()
    {
        //TODO shoot player
    }
    
    
}