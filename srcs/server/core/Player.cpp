#include <algorithm>
#include "MissileFactory.hpp"
#include "AMissile.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "ObjectCast.hpp"

namespace Unit {

    const unsigned int          Player::DEFAULTHP = 1;
    const Missile::type         Player::DEFAULTMISSILE = Missile::BASIC;
    const unsigned int          Player::STARTX = 10;
    const unsigned int          Player::STARTY = Map::HEIGHT / 2;
    const boxType               Player::DEFAULTHITBOX = std::make_pair(10, 10);

    Player::Player(color c, std::string name, unsigned int id, unsigned int gameID)
    : AUnit(DEFAULTHP, ALLY, STARTX, STARTY, DEFAULTHITBOX, RIGTH, id, gameID), _color(c), _name(name), _score(0), _weapon(DEFAULTMISSILE), _time(0), _isMoving(), _isShooting(0)
    {
        for (int i = 0; i < 4; i++)
            _isMoving[i] = false;
    }

    Player::~Player()
    {
    }

    Missile::AMissile*          Player::shoot()
    {
        if (!_time.isFinished())
            return NULL;

      //TODO: FIND A WAY TO GET A ID
        Missile::AMissile *m = Missile::Factory::getInstance()->getObject(_weapon, _x, _y, this, _dir, 0);

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
        return _name;
    }

    color                       Player::getColor() const
    {
        return _color;
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
        unsigned int            x = _x, y = _y;
        
        if ((tab[to][0] == -1 && !_x) || (tab[to][0] == 1 && _x == Map::WIDTH) || (tab[to][1] == -1 && !_y) || (tab[to][1] == 1 && _y == Map::HEIGHT))
            return false;
        _x += tab[to][0];
        _y += tab[to][1];
        
        AUnit *unit = map->checkInterractions(this);
        if (unit && unit->getType() == OBSTACLE)
        {
            _x = x;
            _y = y;
            return false;
        }
        return true;
    }

    type                        Player::getType() const
    {
        return PLAYER;
    }
    
    bool                        Player::isMoving(Unit::dir d) const
    {
        return _isMoving[d];
    }
    
    bool                        Player::isShooting() const
    {
        return _isShooting;
    }
    
    void                        Player::checkMouvement(AUnit *unit, IMap *map)
    {
        Unit::Player *player = ObjectCast::getObject<Unit::Player*>(unit);
        
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
