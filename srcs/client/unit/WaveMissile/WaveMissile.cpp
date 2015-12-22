#include <iostream>
#include <cmath>
#include "WaveMissile.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport) Unit::WaveMissile *		NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param);
#endif
  Unit::WaveMissile *		NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  {
    return (new Unit::WaveMissile(x, y, id, creationTime, param));
  }

#if (defined _WIN32)
  __declspec(dllexport)   void				DeleteUnit(Unit::WaveMissile * monster);
#endif
  void				DeleteUnit(Unit::WaveMissile * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  WaveMissile::WaveMissile(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  : AUnit(x, y, id, creationTime, param),
  _mySprite(std::string("../resources/sprites/main fire.lvl1.20x14x2.png"), 2),
  _mySound(new SoundPlayer("../resources/sound/LaserShot.ogg"))
  {
    _mySprite.pause();
  }

  WaveMissile::~WaveMissile()
  {
    if (_mySound != NULL)
      delete _mySound;
  }
  
  Unit::pos            WaveMissile::move(Time::stamp tick) const
  {        
    pos p = std::make_pair(_x + (tick * 5 * _param), static_cast<int>(_y + std::sin((tick % 500) / 100.0) * 500.0));

    return p;
  }
    
  void		WaveMissile::render(Time::stamp tick, sf::RenderWindow & window)
  {
    long diff = static_cast<long>(tick - _creationTime) / 10;
    pos p = move(diff);

    if (_mySound != NULL && _mySound->getPlayingOffset() == _mySound->getDuration())
    {
//     std::cout << "finish" << std::endl;
     delete _mySound;
     _mySound = NULL;
   }
    //_mySprite.setRotation();

   _mySprite.setPosition(static_cast<float>(p.first), static_cast<float>(p.second));
   if (diff > 15)
    _mySprite.setFrameIndex(1u); 
  window.draw(_mySprite);
}

typeID	WaveMissile::getType() const
{
  return WAVEMISSILE;
}
}
