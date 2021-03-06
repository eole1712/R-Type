#ifndef MonsterWaveManager_hpp
#define MonsterWaveManager_hpp

#include <stdio.h>

#include "MonsterWave.hpp"
#include "IMap.hpp"
#include "IGameUnitSender.hpp"
#include "GameUtils.hpp"

namespace Monster {
    
    constexpr int   generatePos(int i, int max)
    {
        return ((GameUtils::Map::HEIGHT / max) * i) + ((GameUtils::Map::HEIGHT / max) / 2);
    }
    
    constexpr int   relativePos(int i, int max, int r1, int r2)
    {
        return (((r2 - r1) / max) * i) + (((r2 - r1) / max) / 2) + r1;
    }
    
    class WaveManager
    {
    public:
        WaveManager(IMap *map, unsigned int gameID, IGameUnitSender *);
        virtual ~WaveManager();
        
    public:
        static Wave*       ClassicWave(unsigned int gameID, int diff);
        static Wave*       TriangleWave(unsigned int gameID, int diff);
        static Wave*       MarineWave(unsigned int gameID);
        static Wave*       KamikazeAttack(unsigned int gameID, int diff);
        
    public:
        void        addWave(Wave*);
        void        removeWave(Wave*);
        void        nextAction(Timer::time, IDCreator *idc);
        void        execConfig(Timer::time);
        
    private:
        IMap*               _map;
        std::list<Wave*>    _list;
        unsigned int        _gameID;
        IGameUnitSender*    _owl;
        
    private:
        unsigned int        _t[4];
    };
}

#endif /* MonsterWaveManager_hpp */
