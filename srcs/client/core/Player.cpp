
#include <iostream>
#include <algorithm>
#include "AMissile.hpp"
#include "Player.hpp"

namespace Unit {

  Player::Player(int x, int y, unsigned int id, Timer::time creationTime, std::string name)
    : AUnit(x, y, id, creationTime),
      _color(static_cast<Unit::color>(id % 4)), _name(name), _shooting(false), _weapon(Missile::BASIC),
      _lastVerticalMove(0), _anim(std::string("../../resources/sprites/ship.fly.247x47x3.png"), 3)
  {    
    static sf::Color colors[4] =
      { { 0, 0, 255, 0}, {187, 11, 11, 0}, {243, 214, 23, 0}, {20, 148, 5, 0} };
   
    _anim.pause();
    _anim.setRotation(45);
    _colorShader.loadFromFile("../../resources/shaders/basic.frag",
			      "../../resources/shaders/basic.vert");
    _colorShader.setParameter("color", colors[id % 4]);
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

  /* // localPlayer -> scoring, infoBarRender...
  unsigned int    getScore() const;
  void            incScore(unsigned int);
public:
  unsigned int		_score;

  unsigned int		Player::getScore() const
  {
    return _score;
  }

  void			Player::incScore(unsigned int score)
  {
    _score += score;
  }
  void			Player::renderUI(sf::RenderWindow & window)
  {
  }
  */

  void                  Player::move(dir to, Time::stamp tick)
  {
    static int              tab[4][2] =
      { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };

    if (to == UP)
      _lastVerticalMove = 1;
    else if (to == DOWN)
      _lastVerticalMove = 2;
      
    if (tick != 0)
      {
	_x += tab[to][0] * (100 / tick);
        _y += tab[to][1] * (100 / tick);
      }
  }

  void			Player::getHit(AUnit *)
  {
    //TODO what must do
  }

  type			Player::getType() const
  {
    return PLAYER;
  }

  pos			Player::move() const
  {

  }

  void			Player::render(sf::RenderWindow & window)
  {
    _colorShader.setParameter("texture", sf::Shader::CurrentTexture);
    _anim.setFrameIndex(_lastVerticalMove);
    _anim.setPosition(_x, _y);
    window.draw(_anim.getFrame(), &_colorShader);
    _lastVerticalMove = 0;
  }
}
