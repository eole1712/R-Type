#ifndef SERVER_H_
#define SERVER_H_

#include "Game.hpp"
#include "APacket.hpp"
#include "IPacketHandler.hpp"
#include "NetManager.hpp"
#include "NetServer.hpp"
#include "User.hpp"
#include "IGameUnitSender.hpp"
#include <map>

class Server : public IPacketHandler, IGameUnitSender {
public:

	static constexpr int kPort = 6524;

	Server();
	~Server();

	virtual void handlePacket(APacket* packet, unsigned int id);
    virtual void start();
    
private:
    void startGame(IGame*);
    void refreshTimer(unsigned int idGame, bool end = false);
    void sendToUser(APacket*, int);
    void sendToGame(APacket*, int);
    void sendToAll(APacket*);
    void sendRoomStatus();
    void sendRoomStatus(int);
    bool userExists(int) const;
    IGame* createGame(std::string const&);
public:
    virtual void        sendUnit(Unit::AUnit *unit, unsigned int unitType);
    virtual void        killUnit(unsigned int id, unsigned int gameID);
  virtual void		disconnectPlayer(unsigned int id);

    
private:
  std::vector<std::function<void(APacket* packet, unsigned int id) > > _packetHandlerFuncs;
private:
	NetManager *_netManager;
	NetServer *_netServer;
	std::map<int, User*> _users;
	std::map<int, IGame*> _games;
    
protected:
    Lock                                    _lock;
    std::list<unsigned int>                 _disconnectedID;
    
    Lock                                    _lockEnd;
    Lock                                    _lockSend;
};

#endif // SERVER_H_