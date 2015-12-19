#ifndef SOUNDPLAYER_HPP_
# define SOUNDPLAYER_HPP_

#include <SFML/Audio.hpp>
#include <iostream>

class SoundPlayer
{
private:
  std::string		_soundFileName;
  sf::SoundBuffer	_soundBuffer;
  sf::Music		_music;
  
public:
  SoundPlayer(std::string const&);
  SoundPlayer(){};
  ~SoundPlayer(){};

  void			play();
  void			pause();
  void			setSound(std::string const&);
};

#endif /* !SOUNDPLAYER_HPP_ */
