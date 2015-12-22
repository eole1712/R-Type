#include <algorithm>
#include <iostream>
#include "MonsterWaveManager.hpp"
#include "GameUtils.hpp"
#include "UnitType.hpp"

namespace Monster {
    
    WaveManager::WaveManager(IMap *map, unsigned int gameID, IGameUnitSender* owl)
    : _map(map), _list(), _gameID(gameID), _owl(owl)
    {
        _t[0] = 1;
        _t[1] = 1;
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
        
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < 2; i++) {
                wave->addMonster(Unit::Monster::MONSTERTEST, GameUtils::Map::WIDTH, relativePos(i, j + 1, 100, 700));
            }
            wave->addWaitingTime(1000);
        }
        return wave;
    }
    
    Wave*     WaveManager::TriangleWave(unsigned int gameID)
    {
        Wave*   wave = new Wave(gameID);

        for (int j = 0; j < 3; j++) {

            for (int i = 0; i < (j + 1); i++) {
                wave->addMonster(Unit::Monster::BIGHUNTER, GameUtils::Map::WIDTH, relativePos(i, j + 1, 300, 500));
            }
            wave->addWaitingTime(500);
        }
        return wave;
    }
    
    Wave*     WaveManager::TriangleEmptyWave(unsigned int gameID)
    {
        Wave*   wave = new Wave(gameID);
        
        for (int j = 0; j < 3; j++) {
            
            for (int i = 0; i < (j + 1); i++) {
                wave->addMonster(Unit::Monster::BIGHUNTER, GameUtils::Map::WIDTH, relativePos(i, j + 1, 300, 500));
            }
            wave->addWaitingTime(500);
        }
        return wave;
    }
    
    void        WaveManager::execConfig(Timer::time time)
    {
        if (time > (10000 * _t[0]))
        {
            addWave(Monster::WaveManager::TriangleWave(_gameID));
            _t[0]++;
        }
        if (time > (6000 * _t[1]))
        {
            addWave(Monster::WaveManager::ClassicWave(_gameID));
            _t[1]++;
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
    
    void    WaveManager::nextAction(Timer::time time, IDCreator *idc)
    {
        std::list<Wave*>::iterator it = _list.begin();
        
        while (it != _list.end())
        {
            Unit::AUnit*    unit;
            while ((*it)->isFinished() && (unit = (*it)->getNextMonster(time, idc)))
            {
                this->_map->addUnit(unit);
                _owl->sendUnit(unit, unit->getTypeID());
            }
            if ((*it)->isEmpty())
                it = _list.erase(it);
            else
                it++;
         }
    }
    
}