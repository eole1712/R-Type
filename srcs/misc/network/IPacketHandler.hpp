
#ifndef IPACKETHANDLER_H_
#define IPACKETHANDLER_H_

#include "APacket.hpp"

class IPacketHandler {
	virtual ~IPacketHandler() {};

	virtual void handlePacket(APacket* packet, playerId id) = 0;
};

#endif /* !IPACKETHANDLER_H_ */