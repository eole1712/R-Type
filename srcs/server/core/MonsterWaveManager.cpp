#include <algorithm>
#include <iostream>
#include "MonsterWaveManager.hpp"
#include "GameUtils.hpp"
#include "UnitType.hpp"

namespace Monster {
    
    WaveManager::WaveManager(IMap *map, unsigned int gameID, IGameUnitSender* owl)
    : _map(map), _list(), _gameID(gameID), _owl(owl)
    {
        for (int i = 0; i < 4; i++)
            _t[i] = 1;
    }
    
    WaveManager::~WaveManager()
    {
        std::for_each(_list.begin(), _list.end(), [](Wave* wave){
            if (wave) {
                delete wave;
            }});
    }
    
    Wave*     WaveManager::ClassicWave(unsigned int gameID, int diff)
    {
        Wave*   wave = new Wave(gameID);
        
        for (int j = 0; j < (2 + (diff / 2)); j++) {
            for (int i = 0; i < 2; i++) {
                wave->addMonster(Unit::Monster::MONSTERTEST, GameUtils::Map::WIDTH, relativePos(i, j + 1, 60, 700));
            }
            wave->addWaitingTime(1000);
        }
        return wave;
    }
    
    Wave*     WaveManager::KamikazeAttack(unsigned int gameID, int diff)
    {
        Wave*   wave = new Wave(gameID);
        
        if (diff > 6) diff = 6;
        
        for (int j = 0; j < (diff); j++) {
            wave->addMonster(Unit::Monster::KAMIKAZPLANE, GameUtils::Map::WIDTH, relativePos(j, diff, 60, 790));
        }
        return wave;
    }
    
    Wave*     WaveManager::TriangleWave(unsigned int gameID, int diff)
    {
        Wave*   wave = new Wave(gameID);
        
        if (diff > 7) diff = 7;
        
        for (int j = 0; j < (3 + (diff - 1)); j++) {

            for (int i = 0; i < (j + 1); i++) {
                wave->addMonster(Unit::Monster::BIGHUNTER, GameUtils::Map::WIDTH, relativePos(i, j + 1, 325 - (25 * diff) , 475 + (25 * diff)));
            }
            wave->addWaitingTime(500);
        }
        return wave;
    }
    
    Wave*     WaveManager::MarineWave(unsigned int gameID)
    {
        Wave*   wave = new Wave(gameID);
        
        for (int j = 0; j < 3; j++) {
            wave->addMonster(Unit::Monster::DRBOOM, GameUtils::Map::WIDTH, 724);
            wave->addWaitingTime(500);
        }
        return wave;
    }
    
    void        WaveManager::execConfig(Timer::time time)
    {
        if (time > (15000 * _t[0]))
        {
            addWave(Monster::WaveManager::TriangleWave(_gameID, _t[0]));
            _t[0]++;
        }
        if (time > (8000 * _t[1]))
        {
            addWave(Monster::WaveManager::ClassicWave(_gameID, _t[1]));
            _t[1]++;
        }
        if (time > (4000 * _t[2]))
        {
            addWave(Monster::WaveManager::MarineWave(_gameID));
            _t[2]++;
        }
        if (time > (6000 * _t[3]))
        {
            addWave(Monster::WaveManager::KamikazeAttack(_gameID, _t[3]));
            _t[3]++;
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