#ifndef AUnit_hpp
#define AUnit_hpp

namespace Unit {
    
    enum type = {
        PLAYER,
        MONSTER,
        MISSILE,
        BONUS,
        OBSTACLE
    };

    enum color = {
        BLUE,
        RED,
        YELLOW,
        GREEN
    };

    enum dir = {
        UP,
        DOWN,
        RIGTH,
        LEFT
    };
    
    enum team = {
        ALLY,
        ENNEMY
    };

    typedef std::pair<unsigned int, unsigned int> boxType;
    
class AUnit {

public:
    AUnit(unsigned int hp, unsigned int x, unsigned int y, boxType hitBox);
    ~AUnit();
private:
    AUnit(AUnit const &);
    AUnit &operator=(AUnit const &);
    
public:
    virtual bool    isAlive() const;
    virtual void    getHit(AUnit*) = 0;
    
public:
    virtual unsigned int    getX() const;
    virtual unsigned int    getY() const;
    virtual void            setX(unsigned int x);
    virtual void            setY(unsigned int y);

public:
    virtual boxType   getHitBox() const;
    virtual void    setHitBox(boxType);
    
public:
    virtual bool    isHitting(AUnit*) const;
    
public:
    virtual type    getType() const = 0;

private:
    unsigned int                            _hp;
    unsigned int                            _x;
    unsigned int                            _y;
    boxType                                 _hitBox;
};

}

#endif /* AUnit_hpp */
