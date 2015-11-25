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
    
class AUnit {

public:
    AUnit();
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
    virtual std::pair<unsigned int, unsigned int>   getHitBox() const;
    virtual void    setHitBox(std::pair<unsigned int, unsigned int>);
    
public:
    virtual bool    isHitting(AUnit*) const;
    
public:
    virtual type    getType() const = 0;

};

}

#endif /* AUnit_hpp */
