#include "SoundPlayer.hpp"

SoundPlayer::SoundPlayer(std::string const& fileName)
  : _soundFileName(fileName)
{
  if (!_soundBuffer.loadFromFile(_soundFileName))
    std::cout << "error loading sound file" << std::endl;
  _sound.setBuffer(_soundBuffer);
}

void		SoundPlayer::play()
{
  _sound.play();
}

void		SoundPlayer::pause()
{
  _sound.pause();
}

void		SoundPlayer::setSound(std::string const& fileName)
{
  if (!_soundBuffer.loadFromFile(fileName))
    std::cout << "error loading sound file" << std::endl;
  _sound.setBuffer(_soundBuffer);
}
