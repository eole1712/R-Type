#include <ctime>
#include "Time.hpp"
#include "Animation.hpp"


Animation::Animation(std::string const & image, unsigned int frame, float speed, bool loop, Time::stamp initTime)
  : _initTime(initTime), _frame(frame), _speed(speed), _state(PLAY), _index(0), _loop(loop), _end(false)
{
  _texture.loadFromFile(image.c_str());
  _texture.setRepeated(true);
  setTexture(_texture);
  _frameWidth = _texture.getSize().x / frame;
  _frameHeight = _texture.getSize().y;
  setTextureRect(sf::IntRect(0, 0, _frameWidth, _frameHeight));
}

Animation::~Animation()
{

}

void			Animation::pause()
{
  _state = PAUSE;
}

void			Animation::play()
{
  _state = PLAY;
}

void			Animation::setState(state s)
{
  _state = s;
}

Animation::state	Animation::getState() const
{
  return _state;
}


void			Animation::setTime(Time::stamp const & newTime)
{
  _initTime = newTime;
}

void			Animation::setFrameIndex(unsigned int idx)
{
  setTextureRect(sf::IntRect(static_cast<int>(_frameWidth * (idx % _frame)), 0, _frameWidth, _frameHeight));
  _index = idx % _frame;
}

void			Animation::setFrameIndex(float idx)
{
  setTextureRect(sf::IntRect(static_cast<int>(_frameWidth * idx), 0, _frameWidth, _frameHeight));
}

unsigned int		Animation::getFrameIndex() const
{
  return _index;
}

sf::Sprite const &	Animation::getFrame()
{
  if (!_end && _state == PLAY)
    {
      _index = static_cast<unsigned int>((Time::getTimeStamp() - _initTime) / _speed);

      if (!_loop && _index >= _frame)
	{
	  _state = PAUSE;
	  _end = true;
	  setTextureRect(sf::IntRect(0, 0, 0, 0));
	  return *this;
	}
      _index %= _frame;
       setTextureRect(sf::IntRect(_frameWidth * _index, 0, _frameWidth,_frameHeight));
    }
  return *this;
}

bool			Animation::finish() const
{
  return !_loop && _end;
}

unsigned int		Animation::getFrameWidth() const
{
  return _frameWidth;
}

unsigned int	        Animation::getFrameHeight() const
{
  return _frameHeight;
}
