
#ifndef PACKETHANDLER_H_
#define PACKETHANDLER_H_

#include "IPacketHandler.hpp"
#include <vector>

class PacketHandler : public IPacketHandler {
public:
	PacketHandler();
	virtual ~PacketHandler();

	virtual void handlePacket(APacket* packet, playerId id);
private:
	std::vector<std::function<void(APacket* packet, playerId id) > > _packetHandlerFuncs
};

#endif /* !IPACKETHANDLER_H_ */