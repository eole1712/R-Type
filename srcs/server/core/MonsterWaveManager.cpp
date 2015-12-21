#include <algorithm>
#include <iostream>
#include "MonsterWaveManager.hpp"
#include "GameUtils.hpp"
#include "UnitType.hpp"

namespace Monster {
    
    WaveManager::WaveManager(IMap *map, unsigned int gameID, IGameUnitSender* owl)
    : _map(map), _list(), _gameID(gameID), _owl(owl)
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
    
    void        WaveManager::execConfig()
    {
        static int t[] = {1, 1};
        
        if (GameUtils::Game::now(_gameID) > (10000 * t[0]))
        {
            addWave(Monster::WaveManager::TriangleWave(_gameID));
            t[0]++;
        }
        if (GameUtils::Game::now(_gameID) > (6000 * t[1]))
        {
            addWave(Monster::WaveManager::ClassicWave(_gameID));
            t[1]++;
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
                _owl->sendUnit(unit, unit->getTypeID());
                std::cout << "Ajout de monstre" << std::endl;
            }
            if ((*it)->isEmpty())
                it = _list.erase(it);
            else
                it++;
         }
    }
    
}