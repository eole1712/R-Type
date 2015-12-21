#include <map>
#include <string>
#include "SoundPlayer.hpp"

SoundPlayer::SoundPlayer(std::string const& fileName, bool loop, float volume)
  : sf::Music()
{
  /*
  static std::map<std::string, sf::InputSoundFile>		cacheFile;
  std::map<std::string, sf::Music>::const_iterator	cacheIndex;

  if ((cacheIndex = cacheFile.find(fileName)) != cacheFile.end())
    this = cacheIndex->second;
  else if (!openFromFile(fileName))
    std::cout << "Error loading music file \"" << fileName << "\"" << std::endl;
  else
    {
      std::cout << "cached :" << fileName << std::end;
      cacheFile[fileName] = this;
    }
  */
  if (!openFromFile(fileName))
    std::cout << "Error loading music file \"" << fileName << "\"" << std::endl;
  setVolume(volume);
  setLoop(loop);
  play();
}

SoundPlayer::~SoundPlayer()
{
}

  //_music.setPosition(0, 1, 10);
  //_music.setPitch(2);           // increase the pitch
