#include <ctime>
#include "Time.hpp"
#include "Animation.hpp"


Animation::Animation(std::string const & image, unsigned int frame, float speed, Time::stamp initTime)
  : _initTime(initTime), _frame(frame), _speed(speed), _state(PLAY), _index(0)
{
  _texture.loadFromFile(image.c_str());
  _texture.setRepeated(true);
  setTexture(_texture);
  _frameWidth = _texture.getSize().x / frame;
  _frameHeight = _texture.getSize().y;
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
  if (_state == PLAY)
    {
      _index = static_cast<unsigned int>((Time::getTimeStamp() - _initTime) / _speed);
      _index %=  _frame;
       setTextureRect(sf::IntRect(_frameWidth * _index, 0, _frameWidth,_frameHeight));
    }
  return *this;
}


unsigned int		Animation::getFrameWidth() const
{
  return _frameWidth;
}

unsigned int	        Animation::getFrameHeight() const
{
  return _frameHeight;
}
