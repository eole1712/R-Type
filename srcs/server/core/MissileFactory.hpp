#ifndef MISSILEFACTORY_H_
# define MISSILEFACTORY_H_

#include <map>
#include "AMissile.hpp"

namespace Unit
{
    namespace Missile
    {
        class Factory
        {
        public:
            Factory();
            ~Factory();
            
        public:
            static Factory	*getInstance();
            static void     destroy();
            void            init();
            AMissile*       getObject(Missile::type);
            AMissile*       getObject(Missile::type, unsigned int x, unsigned int y, AUnit*);
            
        private:
            Factory(Factory const& other);
            Factory&	operator=(Factory const& other);
        
        protected:
            std::map<Missile::type, AMissile*> _map;
        };
        
        static Factory *_instance = NULL;
    }
}


#endif /* !MISSILEFACTORY_H_ */
