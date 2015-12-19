#include "SoundPlayer.hpp"

SoundPlayer::SoundPlayer(std::string const& fileName)
  : _soundFileName(fileName), _music()
{
  if (!_music.openFromFile(_soundFileName))
    std::cout << "error loading music file" << std::endl;
  //_sound.setBuffer(_soundBuffer);
}

void		SoundPlayer::play()
{
  _music.setPosition(0, 1, 10); // change its 3D position
  //_music.setPitch(2);           // increase the pitch
  _music.setVolume(50);         // reduce the volume
  _music.setLoop(true);
  _music.play();
}

void		SoundPlayer::pause()
{
  _music.pause();
}

void		SoundPlayer::setSound(std::string const& fileName)
{
  if (!_music.openFromFile(fileName))
    std::cout << "error loading music file" << std::endl;
  //  _sound.setBuffer(_soundBuffer);
}
