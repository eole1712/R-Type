
#ifndef PACKETHANDLER_H_
#define PACKETHANDLER_H_

#include "IPacketHandler.hpp"

class PacketHandler : public IPacketHandler {
	PacketHandler();
	virtual ~PacketHandler();

	virtual void handlePacket(APacket* packet, playerId id);
};

#endif /* !IPACKETHANDLER_H_ */