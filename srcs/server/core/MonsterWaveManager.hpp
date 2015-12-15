#ifndef MonsterWaveManager_hpp
#define MonsterWaveManager_hpp

#include <stdio.h>

#include "MonsterWave.hpp"
#include "IMap.hpp"

namespace Monster {
    
    class WaveManager
    {
    public:
        WaveManager(IMap *map, unsigned int gameID);
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
        Timer*              _timer;
        unsigned int        _gameID;
    };
}

#endif /* MonsterWaveManager_hpp */
