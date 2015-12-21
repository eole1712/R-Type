#ifndef SOUNDPLAYER_HPP_
# define SOUNDPLAYER_HPP_

#include <SFML/Audio.hpp>
#include <iostream>

class SoundPlayer : public sf::Music
{
private:
  
public:
  SoundPlayer(std::string const&, bool loop = false, float volume = 50);
  virtual ~SoundPlayer();
};

#endif /* !SOUNDPLAYER_HPP_ */
