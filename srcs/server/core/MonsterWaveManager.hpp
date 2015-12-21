#ifndef MonsterWaveManager_hpp
#define MonsterWaveManager_hpp

#include <stdio.h>

#include "MonsterWave.hpp"
#include "IMap.hpp"
#include "IGameUnitSender.hpp"

namespace Monster {
    
    class WaveManager
    {
    public:
        WaveManager(IMap *map, unsigned int gameID, IGameUnitSender *);
        virtual ~WaveManager();
        
    public:
        static Wave*       ClassicWave(unsigned int gameID);
        
    public:
        void        addWave(Wave*);
        void        removeWave(Wave*);
        void        nextAction();
        void        execConfig(Timer &time);
        
    private:
        IMap*               _map;
        std::list<Wave*>    _list;
        unsigned int        _gameID;
        IGameUnitSender*    _owl;
    };
}

#endif /* MonsterWaveManager_hpp */
