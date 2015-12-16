#include <map>
#include "GameUtils.hpp"

namespace GameUtils {
    
    namespace Game {
        
        unsigned int            getNewID(unsigned int gameID)
        {
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
        
        bool            isIn(int x, int y)
        {
            if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
                return false;
            return true;
        }
    }
}