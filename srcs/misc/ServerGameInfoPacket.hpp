
#ifndef SERVERGAMEINFOPACKET_H_
#define SERVERGAMEINFOPACKET_H_ 

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE|||||||||||||||||||||||||||||||
// IDPACKET||TYPEPACKET||ROOMID||SLOTS||READY||ROOMNAME|||

class ServerGameInfoPacket : public APacket {
public:

	static constexpr int kRoomNameSize = 30;

	ServerGameInfoPacket();
	ServerGameInfoPacket(std::string const& data);
	virtual ~ServerGameInfoPacket();

	uint32_t getRoomId();
	uint8_t getRoomSlots();
    uint8_t getRoomReady();
	std::string getRoomName();

	void setRoomId(uint32_t id);
	void setRoomSlots(uint8_t nb);
    void setRoomReady(uint8_t nb);
	void setRoomName(std::string const& name);
};

#endif /* !SERVERGAMEINFOPACKET_H_ */