
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
//        bool             isIn(int x, int y);
        bool            isInBas(int y1, unsigned int y2);
        bool            isInBox(int x, int y, unsigned int x1);
        
        static const int        WIDTH = 1200;
        static const int        HEIGHT = 800;
    }
}


#endif /* GameUtils_hpp */
