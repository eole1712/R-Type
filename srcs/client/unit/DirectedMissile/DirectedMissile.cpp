#include <iostream>
#include <cmath>
#include "DirectedMissile.hpp"

extern "C"
{
#if (defined _WIN32)
	__declspec(dllexport) Unit::DirectedMissile *		NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param);
#endif
  Unit::DirectedMissile *		NewUnit(int x, int y, unsigned int id, Time::stamp creationTime, float param)
  {
    return (new Unit::DirectedMissile(x, y, id, creationTime, param));
  }

#if (defined _WIN32)
  __declspec(dllexport)   void				DeleteUnit(Unit::DirectedMissile * monster);
#endif
  void				DeleteUnit(Unit::DirectedMissile * monster)
  {
    delete monster;
  }
}

namespace Unit
{
  DirectedMissile::DirectedMissile(int x, int y, unsigned int id, Time::stamp creationTime, float param)
    : AUnit(x, y, id, creationTime, param),
      _mySprite(std::string("../resources/sprites/dickbutt.fly.33x22x8.png"), 8),
      _mySound(new SoundPlayer("../resources/sound/LaserShot.ogg"))
  {
      _mySprite.scale(0.5f, 0.5f);
      _mySprite.setRotation(27);
//    _mySprite.pause();
  }

  DirectedMissile::~DirectedMissile()
  {
    if (_mySound != NULL)
      delete _mySound;
  }
  
  Unit::pos            DirectedMissile::move(Time::stamp tick) const
  {
    pos p = std::make_pair(static_cast<int>(_x + (tick * 5 * _param)), _y - tick * 3);
    
    return p;
  }
  
  void		DirectedMissile::render(Time::stamp tick, sf::RenderWindow & window)
  {
    long diff = static_cast<long>(tick - _creationTime) / 10;
    pos p = move(diff);

    if (_mySound != NULL && _mySound->getPlayingOffset() == _mySound->getDuration())
      {
	delete _mySound;
	_mySound = NULL;
      }
    //_mySprite.setRotation();
 
    _mySprite.setPosition(static_cast<float>(p.first), static_cast<float>(p.second));
    if (diff > 15)
      _mySprite.setFrameIndex(1u); 
    window.draw(_mySprite);
  }

  typeID	DirectedMissile::getType() const
  {
    return DIRECTEDMISSILE;
  }
}
