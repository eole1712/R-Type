#ifndef ANIMATION_HPP_
# define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <vector>

class Animation : public sf::Sprite
{
public:
  Animation(std::string const & image, unsigned int frame, unsigned int speed, int initTime);
  virtual ~Animation();

private:
  int			_initTime;
  unsigned int		_frameWidth;
  unsigned int		_frameHeight;
  unsigned int		_frame;
  unsigned int		_speed;
  sf::Texture		_texture;
  
public:

  sf::Sprite const &	getFrame();
};

#endif /* !ANIMATION_HPP_ */ 
