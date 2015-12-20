#include <algorithm>
#include <iostream>
#include "MonsterWaveManager.hpp"
#include "GameUtils.hpp"

namespace Monster {
    
    WaveManager::WaveManager(IMap *map, unsigned int gameID)
    : _map(map), _list(), _gameID(gameID)
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
                wave->addMonster(Unit::Monster::MONSTERTEST, GameUtils::Map::WIDTH - 1, i * (GameUtils::Map::HEIGHT / 3));
            }
            wave->addWaitingTime(1000);
            wave->addMonster(Unit::Monster::MONSTERTEST, GameUtils::Map::WIDTH - 1, GameUtils::Map::HEIGHT / 2);
            wave->addWaitingTime(1000);
        }
        return wave;
    }
    
    void        WaveManager::execConfig(Timer &time)
    {
        static int t[] = {1};
        
        if (GameUtils::Game::now(_gameID) > (10000 * t[0]))
        {
            addWave(Monster::WaveManager::ClassicWave(_gameID));
            t[0]++;
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
        std::list<Wave*>::iterator it = _list.begin();
        
        while (it != _list.end())
        {
            Unit::AUnit*    unit;
            while ((*it)->isFinished() && (unit = (*it)->getNextMonster()))
            {
                this->_map->addUnit(unit);
                std::cout << "Ajout de monstre" << std::endl;
            }
            if ((*it)->isEmpty())
                it = _list.erase(it);
            else
                it++;
         }
    }
    
}