#include <algorithm>
#include "MonsterWaveManager.hpp"
#include "Map.hpp"

namespace Monster {
  
  WaveManager::WaveManager(IMap *map, unsigned int gameID)
  : _map(map), _list(), _timer(0), _gameID(gameID)
  {
  }
  
  WaveManager::~WaveManager()
  {
    std::for_each(_list.begin(), _list.end(), [](Wave* wave){
      if (wave) {
        delete wave;
      }});
  }
  
  Wave*     WaveManager::ClassicWave(unsigned int gameID)
  {
    Wave*   wave = new Wave(gameID);
    
    for (int j = 0; j < 3; j++) {
      for (int i = 0; i < 3; i++) {
        wave->addMonster(Unit::Monster::MONSTERTEST, Map::WIDTH - 1, i * (Map::HEIGHT / 3));
      }
      wave->addWaitingTime(2);
      wave->addMonster(Unit::Monster::MONSTERTEST, Map::WIDTH - 1, Map::HEIGHT / 2);
      wave->addWaitingTime(2);
    }
    return wave;
  }
  
  void    WaveManager::execConfig(Timer &time)
  {
    if ((time.getElapsedTime() % 10000) == 0)
    {
      addWave(Monster::WaveManager::ClassicWave(_gameID));
    }
  }
  
  void    WaveManager::addWave(Wave* wave)
  {
    _list.push_back(wave);
  }
  
  void    WaveManager::removeWave(Wave* wave)
  {
    if (wave)
    {
      _list.remove(wave);
      delete wave;
    }
  }
  
  void    WaveManager::nextAction()
  {
    std::for_each(_list.begin(), _list.end(), [this](Wave *wave){

      Unit::AUnit*    unit;
      while (wave->isFinished() && (unit = wave->getNextMonster()))
        {
          this->_map->addUnit(unit);
        }
    });
    for (std::list<Wave*>::iterator it = _list.begin(); it != _list.end(); it++)
    {
      if ((*it)->isEmpty())
        it = _list.erase(it);
    }
  }
  
}