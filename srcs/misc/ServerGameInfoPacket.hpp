
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

	uint32_t getRoomId() const;
	uint8_t getRoomSlots() const;
    uint8_t getRoomReady() const;
    bool getUserReady() const;
	std::string getRoomName() const;

	void setRoomId(uint32_t id);
	void setRoomSlots(uint8_t nb);
    void setRoomReady(uint8_t nb);
    void setUserReady(bool ready);
	void setRoomName(std::string const& name);
};

std::ostream& operator<<(std::ostream& os, ServerGameInfoPacket const& packet);

#endif /* !SERVERGAMEINFOPACKET_H_ */