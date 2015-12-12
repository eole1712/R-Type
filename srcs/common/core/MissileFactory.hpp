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
            AMissile*       getObject(Missile::type, AUnit*, unsigned  int id);

        private:
            Factory(Factory const& other);
            Factory&	operator=(Factory const& other);

        protected:
            std::map<Missile::type, AMissile*> _map;

	public:
	    static Factory *_instance;
	};
    }
}


#endif /* !MISSILEFACTORY_H_ */
