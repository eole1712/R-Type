
#ifndef SERVERPLAYERMOVEPACKET_H_
#define SERVERPLAYERMOVEPACKET_H_

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE|||||||||||||||
// IDPACKET||TYPEPACKET||PLAYERID||X||Y|||

class ServerPlayerMovePacket : public APacket {
public:

	ServerPlayerMovePacket();
	ServerPlayerMovePacket(std::string const& data);
	virtual ~ServerPlayerMovePacket();

	uint32_t getPlayerID();
	uint32_t getX();
    uint32_t getY();

	void setPlayerID(uint32_t id);
    void setX(uint32_t id);
    void setY(uint32_t id);
};

std::ostream& operator<<(std::ostream& os, ServerPlayerMovePacket const& packet);

#endif /* !SERVERPLAYERMOVEPACKET_H_ */