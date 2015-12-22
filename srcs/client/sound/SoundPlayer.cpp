#include <map>
#include <string>
#include "SoundPlayer.hpp"

static unsigned int nbSound = 0;

SoundPlayer::SoundPlayer(std::string const& fileName, bool loop, float volume)
  : sf::Music(), _finish(false)
{
//  if (nbSound > 10)
//    {
////      std::cout << "max sound" << std::endl;
//      return ;
//    }
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
  nbSound++;
}

SoundPlayer::~SoundPlayer()
{
  if (nbSound > 0)
    nbSound--;
}

bool SoundPlayer::finish()
{
  return _finish;
}	
