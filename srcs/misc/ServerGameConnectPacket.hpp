
#ifndef SERVERGAMECONNECTPACKET_H_
#define SERVERGAMECONNECTPACKET_H_ 

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE||||||||||||||||||
// IDPACKET||TYPEPACKET||STATUS||PLAYER ID|||

class ServerGameConnectPacket : public APacket {
public:

	static constexpr int kPlayerNameSize = 16;

	ServerGameConnectPacket();
	ServerGameConnectPacket(std::string const& data);
	virtual ~ServerGameConnectPacket();

	bool getStatus() const;
	uint8_t	getPlayerId() const;
	uint32_t getGameId() const;

	void setStatus(bool status);
	void setPlayerId(uint8_t id);
	void setGameId(uint32_t id);
};

std::ostream& operator<<(std::ostream& os, ServerGameConnectPacket const& packet);

#endif /* !SERVERGAMECONNECTPACKET_H_ */