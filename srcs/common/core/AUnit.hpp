#ifndef AUnit_hpp
#define AUnit_hpp

#include <list>

namespace Unit {

  enum type {
    PLAYER,
    MONSTER,
    MISSILE,
    BONUS,
    OBSTACLE
  };

  enum color : unsigned int {
    BLUE,
    RED,
    YELLOW,
    GREEN
  };

  enum dir : int {
    UP,
    DOWN,
    RIGTH,
    LEFT
  };

  enum team {
    ALLY,
    ENEMY
  };

  typedef std::pair<unsigned int, unsigned int> boxType;

  class AUnit {

  public:
    AUnit(unsigned int hp, team t, unsigned int x, unsigned int y, boxType hitBox, dir, unsigned int id, unsigned int gameID);
    virtual ~AUnit();
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
    virtual dir     getDir() const;
    
  public:
    virtual team    getTeam() const;
    virtual void    setTeam(team t);

  public:
    virtual unsigned int  getID() const;
    virtual unsigned int  getGameID() const;

  protected:
    unsigned int                            _hp;
    team                                    _team;
    unsigned int                            _x;
    unsigned int                            _y;
    boxType                                 _hitBox;
    dir                                     _dir;
    unsigned int                            _id;
    unsigned int                            _gameID;
  };

}

#endif /* AUnit_hpp */
