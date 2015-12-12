#ifndef BasicMissile_hpp
#define BasicMissile_hpp

#include "AMissile.hpp"

namespace Unit {

    namespace Missile {
    
        class BasicMissile : public AMissile{
        public:
            BasicMissile(unsigned int x, unsigned int y, AUnit *origin, dir, unsigned int id);
            virtual ~BasicMissile();
            
        public:
            virtual bool                isKillable() const;
            virtual Missile::type       getMissileType() const;
            virtual void                move();
            
        public:
            virtual double              getTime() const;
            
        public:
            virtual void                getHit(AUnit*);
            
        public:
            virtual AMissile*	clone(unsigned int x, unsigned int y, AUnit*, dir, unsigned int id) const;
            virtual std::string	getClassName() const;
        };
    }
}

#endif /* BasicMissile_hpp */
