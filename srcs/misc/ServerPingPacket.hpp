
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

#endif /* !SERVERPINGPACKET_H_ */