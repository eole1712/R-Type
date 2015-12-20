
#ifndef GameUtils_hpp
#define GameUtils_hpp

#include <stdio.h>
#include "Timer.hpp"

namespace GameUtils {
    
    namespace Game {
        
        unsigned int     getNewID(unsigned int id);
        Timer::time      now(unsigned int id);
    }
    
    namespace Map {
        bool             isIn(int x, int y);
        
        static const int        WIDTH = 1600;
        static const int        HEIGHT = 800;
    }
}


#endif /* GameUtils_hpp */
