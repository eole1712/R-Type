#ifndef ANIMATION_HPP_
# define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Time.hpp"

class Animation : public sf::Sprite
{
public:
  Animation(std::string const & image, unsigned int frame = 2,
	    float speed = 100, Time::stamp initTime = Time::getTimeStamp());
  virtual ~Animation();


public:
  enum state { PAUSE, PLAY };

private:
  Time::stamp		_initTime;
  unsigned int		_frameWidth;
  unsigned int		_frameHeight;
  unsigned int		_frame;
  float			_speed;
  state			_state;
  unsigned int		_index;
  sf::Texture		_texture;

public:

  void			pause();
  void			play();

  void			setState(state s);
  state			getState() const;
  void			setFrameIndex(unsigned int idx);
  unsigned int		getFrameIndex() const;
  sf::Sprite const &	getFrame();
};

#endif /* !ANIMATION_HPP_ */
