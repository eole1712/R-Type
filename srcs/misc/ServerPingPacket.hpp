
#ifndef SERVERPINGPACKET_H_
#define SERVERPINGPACKET_H_

#include "APacket.hpp"

// ||||||||||PACKETSIZE||||||||||
// IDPACKET||TYPEPACKET||STATUS||

class ServerPingPacket : public APacket {
public:

	ServerPingPacket();
	ServerPingPacket(std::string const& data);
	virtual ~ServerPingPacket();

    bool getStatus();

    void        setStatus(bool);
};

std::ostream& operator<<(std::ostream& os, ServerPingPacket const& packet);

#endif /* !SERVERPINGPACKET_H_ */