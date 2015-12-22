#include <algorithm>
#include <map>
#include <iostream>
#include "MissileFactory.hpp"
#include "AMissile.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "GameUtils.hpp"
#include "Game.hpp"
#include "ObjectCast.hpp"

namespace Unit {

    const unsigned int          Player::DEFAULTHP = 1;
    const Missile::type         Player::DEFAULTMISSILE = Missile::BASIC;
    const unsigned int          Player::STARTX = 10;
    const unsigned int          Player::STARTY = GameUtils::Map::HEIGHT / 2;
    const boxType               Player::DEFAULTHITBOX = std::make_pair(85, 47);

    Player::Player(color c, User* user, unsigned int id, unsigned int gameID)
    : AUnit(DEFAULTHP, ALLY, STARTX, STARTY, DEFAULTHITBOX, id, gameID, GameUtils::Game::now(gameID)), _color(c), _score(0), _weapon(DEFAULTMISSILE), _time(0), _isMoving(), _isShooting(0), _user(user), _lock()
    {
        for (int i = 0; i < 4; i++)
            _isMoving[i] = false;

        _user->startGame(gameID, this);
    }

    Player::~Player()
    {
        if (_user)
            _user->endGame(_score);
    }

    Missile::AMissile*          Player::shoot(Timer::time time)
    {
        if (!_time.isFinished())
            return nullptr;

      Missile::AMissile *m = Missile::Factory::getInstance()->createMissile(_weapon, this,
                                                                            0, time);

        _time.reset(static_cast<uintmax_t>(m->getTime() * 1000));

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

    void                        Player::getHit(AUnit *unit)
    {
        if (unit->getType() == MISSILE || unit->getType() == MONSTER) {
            if (_hp > 0)
                _hp--;
        }
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
        return _user->getName();
    }

    User*                       Player::getUser() const
    {
        return _user;
    }

    color                       Player::getColor() const
    {
        return _color;
    }

    pos                         Player::move(Timer::time) const
    {
      return std::make_pair(_x, _y);
    }

    bool                        Player::move(dir to, IMap *map)
    {
        static int              tab[4][2] =
        {
            {0, -5},
            {0, 5},
            {5, 0},
            {-5, 0}
        };
        
        if (GameUtils::Map::isIn(_x + tab[to][0], _y + tab[to][1], _hitBox.first) == false)
            return false;
        _x += tab[to][0];
        _y += tab[to][1];
        _user->setRefresh(true);
        return true;
    }

    type                        Player::getType() const
    {
        return PLAYER;
    }

    bool                        Player::isMoving(Unit::dir d)
    {
        std::lock_guard<Lock>   lock(_lock);
        return _isMoving[d];
    }

    void                        Player::setMoving(Unit::dir dir, bool isMoving) {
        std::lock_guard<Lock>   lock(_lock);
        _isMoving[dir] = isMoving;
    }

    bool                        Player::isShooting()
    {
        std::lock_guard<Lock>   lock(_lock);

        return _isShooting;
    }

    void                        Player::setShooting(bool isShooting) {
        std::lock_guard<Lock>   lock(_lock);
        _isShooting = isShooting;
    }

    void                        Player::checkMouvement(Player *player, IMap *map)
    {
        for (Unit::dir i = Unit::UP; i <= Unit::LEFT; i = static_cast<Unit::dir>(static_cast<int>(i) + 1))
        {
            if (player->isMoving(i))
            {
                player->move(i, map);
                if (i == Unit::UP || i == Unit::RIGTH)
                    i = static_cast<Unit::dir>(static_cast<int>(i) + 1);
            }
        }
    }
    
    Unit::typeID  Player::getTypeID() const
    {
        return PLAYERTYPE;
    }
    
    void          Player::setX(int x)
    {
        _x = x;
    }

    void          Player::setY(int y)
    {
        _y = y;
    }
    
    void          Player::setUser(User *user)
    {
        _user = user;
    }
}
