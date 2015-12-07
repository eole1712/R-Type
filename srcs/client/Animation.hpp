#ifndef ANIMATION_HPP_
# define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Time.hpp"

namespace RType
{

class Animation : public sf::Sprite
{
public:
  Animation(std::string const & image, unsigned int frame, float speed, Time::stamp initTime);
  virtual ~Animation();

private:
  Time::stamp		_initTime;
  unsigned int		_frameWidth;
  unsigned int		_frameHeight;
  unsigned int		_frame;
  float			_speed;
  sf::Texture		_texture;

public:

  sf::Sprite const &	getFrame();
};

};

#endif /* !ANIMATION_HPP_ */
