#ifndef MonsterWaveManager_hpp
#define MonsterWaveManager_hpp

#include <stdio.h>

#include "MonsterWave.hpp"
#include "IMap.hpp"

namespace Monster {
    
    class WaveManager
    {
    public:
        WaveManager(IMap *map);
        virtual ~WaveManager();
        
    public:
        static Wave*       ClassicWave(unsigned int gameID);
        
        
    public:
        void        addWave(Wave*);
        void        removeWave(Wave*);
        void        nextAction();
        
    private:
        IMap*               _map;
        std::list<Wave*>    _list;
        Timer*              _timer;
    };
}

#endif /* MonsterWaveManager_hpp */
