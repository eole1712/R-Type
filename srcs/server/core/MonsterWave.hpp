#ifndef MonsterWave_hpp
#define MonsterWave_hpp

#include <stdio.h>
#include "Timer.hpp"
#include "AUnit.hpp"
#include "AMonster.hpp"
#include "MonsterLabel.hpp"

namespace Monster {
    
    class Wave : public Timer {
    public:
        Wave(unsigned int _gameID);
        ~Wave();
        
    public:
        bool            addMonster(Unit::Monster::type, int x, int y);
        bool            addWaitingTime(Timer::time);
        
    public:
        bool            start();
        Unit::AUnit     *getNextMonster();
        
    private:
        bool                        _started;
        Timer::time                 _time;
        std::list<Label>            _list;
        unsigned int                _gameID;
    };
}

#endif /* MonsterWave_hpp */
