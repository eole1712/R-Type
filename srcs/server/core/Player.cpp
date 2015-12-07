#include <algorithm>
#include "MissileFactory.hpp"
#include "AMissile.hpp"
#include "Player.hpp"
#include "Map.hpp"

namespace Unit {

    const unsigned int          Player::DEFAULTHP = 1;
    const Missile::type         Player::DEFAULTMISSILE = Missile::BASIC;
    const unsigned int          Player::STARTX = 10;
    const unsigned int          Player::STARTY = Map::HEIGHT / 2;
    const boxType               Player::DEFAULTHITBOX = std::make_pair(10, 10);

    Player::Player(color c, std::string name)
    : AUnit(DEFAULTHP, ALLY, STARTX, STARTY, DEFAULTHITBOX), _color(c), _name(name), _score(0), _weapon(DEFAULTMISSILE), _time(0)
    {
    }

    Player::~Player()
    {
    }

    Missile::AMissile*          Player::shoot()
    {
        if (!_time.isFinished())
            return NULL;

        Missile::AMissile *m = Missile::Factory::getInstance()->getObject(_weapon, _x, _y, this);

        _time.reset(m->getTime());

        return m;
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

        if ((tab[to][0] == -1 && !_x) || (tab[to][0] == 1 && _x == Map::WIDTH) || (tab[to][1] == -1 && !_y) || (tab[to][1] == 1 && _y == Map::HEIGHT))
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
