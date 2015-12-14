
#ifndef CLIENTGAMECONNECTPACKET_H_
#define CLIENTGAMECONNECTPACKET_H_ 

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE||||||||||||||||||
// IDPACKET||TYPEPACKET||IDROOM||ROOM NAME|||

class ClientGameConnectPacket : public APacket {
public:

	static constexpr int kRoomNameSize = 16;

	ClientGameConnectPacket();
	ClientGameConnectPacket(std::string const& data);
	virtual ~ClientGameConnectPacket();

	uint32_t getRoomId();
	std::string getRoomName();

	void	setRoomId(uint32_t id);
	void	setRoomName(std::string const& name);
};

#endif /* !CLIENTGAMECONNECTPACKET_H_ */