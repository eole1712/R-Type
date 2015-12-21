#include <map>
#include "Lock.hpp"
#include "GameUtils.hpp"
#include <mutex>

namespace GameUtils {
    
    namespace Game {
        
        unsigned int            getNewID(unsigned int gameID)
        {
            static Lock         lock;
            
            std::lock_guard<Lock> l(lock);
            
            static std::map<unsigned int, unsigned int>   tab;
            std::map<unsigned int, unsigned int>::iterator it;
            
            it = tab.find(gameID);
            if (it == tab.end())
                tab[gameID] = 5;
            else
                tab[gameID]++;
            return tab[gameID];
        }
        
        Timer::time             now(unsigned int gameID)
        {
            static Lock         lock;
            
            std::lock_guard<Lock> l(lock);
            
            static std::map<unsigned int, Timer*>   tab;
            std::map<unsigned int, Timer*>::iterator it;
            
            it = tab.find(gameID);
            if (it == tab.end())
            {
                tab[gameID] = new Timer(0);
            }
            return tab[gameID]->getElapsedTime();
        }
    }
    
    namespace Map {
        
        bool            isInBas(int y1, unsigned int y2)
        {
            if (y1 + y2 > HEIGHT)
                return false;
            return true;
        }
        
//        bool            isIn(int x, int y)
//        {
//            if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
//                return false;
//            return true;
//        }
        
        bool            isInBox(int x, int y, unsigned int x1)
        {
            if (x < 0 || y < 0 || (x + x1) > WIDTH)
                return false;
            return true;
        }
    }
}