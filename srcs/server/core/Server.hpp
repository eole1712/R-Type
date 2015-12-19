#ifndef SERVER_H_
#define SERVER_H_

#include "Game.hpp"
#include "APacket.hpp"
#include "IPacketHandler.hpp"
#include "NetManager.hpp"
#include "NetServer.hpp"
#include "User.hpp"
#include <map>

class Server : public IPacketHandler {
public:

	static constexpr int kPort = 6524;

	Server();
	~Server();

	virtual void handlePacket(APacket* packet, unsigned int id);
    virtual void start();
    
private:
    void startGame(IGame*);
    void refreshTimer(unsigned int idGame);
    
    
private:
  std::vector<std::function<void(APacket* packet, unsigned int id) > > _packetHandlerFuncs;
private:
	NetManager *_netManager;
	NetServer *_netServer;
	std::map<int, User*> _users;
	std::map<int, IGame*> _games;
};

#endif // SERVER_H_