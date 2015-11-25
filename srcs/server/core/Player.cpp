
#include <algorithm>
#include "Player.hpp"
#include "Map.hpp"

namespace Unit {

    const unsigned int          Player::defaultHP = 1;
    const Missile::type         Player::defaultMissile = Missile::BASIC;
    const unsigned int          Player::startX = 10;
    const unsigned int          Player::startY = Map::height / 2;
    const boxType               Player::defaultHitBox = std::make_pair(10, 10);
    
    Player::Player(color c, std::string name)
    : AUnit(defaultHP, ALLY, startX, startY, defaultHitBox), _color(c), _name(name), _score(0), _weapon(defaultMissile)
    {
    }
    
    Player::~Player()
    {
    }
    
    Missile::AMissile*          Player::shoot()
    {
        //TODO shoot player
        return NULL;
    }
    
    Missile::type               Player::getWeapon() const
    {
        return _weapon;
    }
    
    void                        Player::setWeapon(Missile::type w)
    {
        _weapon = w;
    }
    
    void                        Player::getHit(AUnit *)
    {
        //TODO what must do
    }

    unsigned int                Player::getScore() const
    {
        return _score;
    }
    
    void                        Player::incScore(unsigned int score)
    {
        _score += score;
    }
    
    std::string                 Player::getName() const
    {
        return _name;
    }
    
    color                       Player::getColor() const
    {
        return _color;
    }
    
    bool                        Player::move(dir to)
    {
        static int              tab[4][2] =
        {
            {0, 1},
            {0, -1},
            {1, 0},
            {-1, 0}
        };

        if ((tab[to][0] == -1 && !_x) || (tab[to][0] == 1 && _x == Map::width) || (tab[to][1] == -1 && !_y) || (tab[to][1] == 1 && _y == Map::height))
            return false;
        _x += tab[to][0];
        _y += tab[to][1];
        return true;
    }
    
    type                        Player::getType() const
    {
        return PLAYER;
    }
}