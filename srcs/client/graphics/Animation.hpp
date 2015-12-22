#ifndef ANIMATION_HPP_
# define ANIMATION_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include "Time.hpp"

class Animation : public sf::Sprite
{
public:
  Animation(std::string const & image, unsigned int frame = 2,
	    float speed = 100, bool loop = true, Time::stamp initTime = Time::getTimeStamp());
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
  bool			_loop;
  bool			_end;

public:

  void			pause();
  void			play();
  void			setState(state s);
  state			getState() const;
  void			setTime(Time::stamp const &);
  void			setFrameIndex(unsigned int idx);
  void			setFrameIndex(float idx);
  unsigned int		getFrameWidth() const;
  unsigned int	        getFrameHeight() const;
  unsigned int		getFrameIndex() const;
  bool			finish() const;
  sf::Sprite const &	getFrame();
};

#endif /* !ANIMATION_HPP_ */
