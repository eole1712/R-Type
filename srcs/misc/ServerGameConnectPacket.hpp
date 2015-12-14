
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

	bool getStatus();
	uint8_t	getPlayerId();

	void setStatus(bool status);
	void setPlayerId(uint8_t id);
};

#endif /* !SERVERGAMECONNECTPACKET_H_ */