
#ifndef CLIENTGAMEINFOPACKET_H_
#define CLIENTGAMEINFOPACKET_H_ 

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE||||||||||||||||||
// IDPACKET||TYPEPACKET||||||||||||||||||||||

class ClientGameInfoPacket : public APacket {
public:
	ClientGameInfoPacket();
	ClientGameInfoPacket(std::string const& data);
	virtual ~ClientGameInfoPacket();
};

std::ostream& operator<<(std::ostream& os, ClientGameInfoPacket const& packet);

#endif /* !CLIENTGAMEINFOPACKET_H_ */