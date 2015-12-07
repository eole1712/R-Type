#include <unistd.h>
#include <iostream>
#include "Timer.hpp"

Timer::Timer(uintmax_t time)
  :_time(std::chrono::microseconds(time)),
   _saveTime(0),
   _clock(std::chrono::system_clock::now()), _freeze(false)
{
  _freeze = false;
}

Timer::~Timer()
{}

void	Timer::start()
{
  _freeze = false;
  _clock = std::chrono::system_clock::now();
}

void	Timer::stop()
{
  _saveTime += getCurTime();
  _freeze = true;
}

void	Timer::reset()
{
  _clock = std::chrono::system_clock::now();
  _saveTime = std::chrono::microseconds(0);
}

void	Timer::reset(uintmax_t time)
{
  _clock = std::chrono::system_clock::now();
  _time = std::chrono::microseconds(time);
  _saveTime = std::chrono::microseconds(0);
}

bool	Timer::isFinished()
{
  return (this->getCurTime() > _time);
}

uintmax_t			Timer::getElapsedTime() const
{
  return (getCurTime().count());
}

std::chrono::microseconds	Timer::getCurTime() const
{
  std::chrono::time_point<std::chrono::system_clock> newTime;

  if (_freeze)
    {
      newTime = _clock;
    }
  else
    newTime = std::chrono::system_clock::now();
  return (_saveTime + std::chrono::duration_cast<std::chrono::microseconds>((newTime - _clock)));
}
