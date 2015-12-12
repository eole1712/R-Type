#include <algorithm>
#include "MissileFactory.hpp"
#include "AMissile.hpp"
#include "Player.hpp"

namespace Unit {

  const unsigned int	Player::DEFAULTHP = 1;
  const Missile::type	Player::DEFAULTMISSILE = Missile::BASIC;
  const unsigned int	Player::STARTX = 10;
  const unsigned int	Player::STARTY = 0;
  const boxType		Player::DEFAULTHITBOX = std::make_pair(10, 10);
  
  Player::Player(color c, std::string name, unsigned int id)
    : AUnit(DEFAULTHP, ALLY, STARTX, STARTY, DEFAULTHITBOX, RIGHT, id),
      _color(c), _name(name), _shooting(0), _weapon(DEFAULTMISSILE), _score(0),
      _anim(std::string("../../ressources/sprites/red ship2.fly.33x36x8.png"), 8, 100, Time::getTimeStamp())
  {
    static sf::Color colors[4] =
      { { 15, 185, 242, 0}, {95, 242, 15, 0}, {96, 245, 241, 0}, {29, 245, 10, 0} };
    _anim.scale(3, 3);
    _colorShader.loadFromFile("../../ressources/shader/default.vert", sf::Shader::Vertex);
    _colorShader.loadFromFile("../../ressources/shader/default.frag", sf::Shader::Fragment);
    _colorShader.setParameter("color", colors[c]);
  }
  
  Player::~Player()
  {
  }
  
  std::string		Player::getName() const
  {
    return _name;
  }
  
  color			Player::getColor() const
  {
    return _color;
  }
  
  bool			Player::isShooting() const
  {
    return _shooting;
  }

  void			Player::shootSend()
  {
    if (_shootTime > 1500)
      _shootTime = 1500;
	/*
        if (!_time.isFinished())
            return NULL;
        Missile::AMissile *m = Missile::Factory::getInstance()->getObject(_weapon, _x, _y, this);
        _time.reset(m->getTime());
        return m;
	 */
  }

  void			Player::shootLoad()
  {

  }
  
  Missile::type		Player::getWeapon() const
  {
    return _weapon;
  }
  
  void			Player::setWeapon(Missile::type w)
  {
    _weapon = w;
  }
    
  unsigned int		Player::getScore() const
  {
    return _score;
  }

  void			Player::incScore(unsigned int score)
  {
    _score += score;
  }
  
  
  void                  Player::move(dir to, Time::stamp tick)
  {
    static int              tab[4][2] =
      { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
  
    _x += (tab[to][0] * 10000) / tick;
    _y += (tab[to][1] * 10000) / tick;
  }
  
  void			Player::getHit(AUnit *)
  {
    //TODO what must do
  }

  type			Player::getType() const
  {
    return PLAYER;
  }

  void			Player::render(sf::RenderWindow & window)
  {
    _anim.setPosition(_x, _y);
    window.draw(_anim.getFrame());
  }
}
