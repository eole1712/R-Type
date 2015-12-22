#ifndef MonsterLabel_hpp
#define MonsterLabel_hpp

#include <stdio.h>

#include "Timer.hpp"
#include "AMonster.hpp"

namespace Monster {

    class Label {
    public:
      Label(Unit::Monster::type, int x, int y, Timer::time);
      ~Label();
    public:
        Label(Label const&);

    public:
        int     getX() const;
        int     getY() const;

    public:
        Unit::Monster::type     getType() const;
        Timer::time             getTime() const;

    private:
        int                     _x;
        int                     _y;
        Unit::Monster::type     _type;
        Timer::time             _time;
    };

}

#endif /* MonsterLabel_hpp */
