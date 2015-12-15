#include <algorithm>
#include <map>
#include "MissileFactory.hpp"
#include "AMissile.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "ObjectCast.hpp"

namespace Unit {

    const unsigned int          Player::DEFAULTHP = 1;
    const Missile::type         Player::DEFAULTMISSILE = Missile::BASIC;
    const unsigned int          Player::STARTX = 10;
    const unsigned int          Player::STARTY = Map::HEIGHT / 2;
    const boxType               Player::DEFAULTHITBOX = std::make_pair(10, 10);

    Player::Player(color c, User* user, unsigned int id, unsigned int gameID)
    : AUnit(DEFAULTHP, ALLY, STARTX, STARTY, DEFAULTHITBOX, id, gameID), _color(c), _score(0), _weapon(DEFAULTMISSILE), _time(0), _isMoving(), _isShooting(0), _user(user), _lock()
    {
        for (int i = 0; i < 4; i++)
            _isMoving[i] = false;
        
        user->startGame(gameID, this);
    }

    Player::~Player()
    {
    }

    Missile::AMissile*          Player::shoot()
    {
        if (!_time.isFinished())
            return NULL;

      Missile::AMissile *m = Missile::Factory::getInstance()->getObject(_weapon, this, Game::getNewID(_gameID));

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
  
    pos                         Player::move() const
    {
      return std::make_pair(_x, _y);
    }

    bool                        Player::move(dir to, IMap *map)
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
}
