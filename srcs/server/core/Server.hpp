#ifndef SERVER_H_
#define SERVER_H_

#include "Game.hpp"
#include <map>

class Server : public IPacketHandler {
public:

	static constexpr kPort = 6524;

	Server();
	~Server();

	virtual void handlePacket(APacket* packet, playerId id);
private:
	std::vector<std::function<void(APacket* packet, playerId id) > > _packetHandlerFuncs
private:
	NetManager *_netManager;
	NetServer *_netServer;
	std::map<int, User*> > _players;
};

#endif SERVER_H_