#include <ctime>
#include "Time.hpp"
#include "Animation.hpp"


Animation::Animation(std::string const & image, unsigned int frame, float speed, Time::stamp initTime)
  : _frame(frame), _initTime(initTime), _speed(speed)
{
  _texture.loadFromFile(image.c_str());
  setTexture(_texture);
  _frameWidth = _texture.getSize().x / frame;
  _frameHeight = _texture.getSize().y;
}

Animation::~Animation()
{

}


sf::Sprite const & Animation::getFrame()
{
  int curFrame = ((Time::getTimeStamp() - _initTime) / _speed);
  curFrame %= _frame;
  setTextureRect(sf::IntRect(_frameWidth * curFrame, 0, _frameWidth,_frameHeight));
  return *this;
}
