
#ifndef SERVERUNITDIEPACKET_H_
#define SERVERUNITDIEPACKET_H_

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE|||||||
// IDPACKET||TYPEPACKET||UNIT ID||

class ServerUnitDiePacket : public APacket {
public:

	ServerUnitDiePacket();
	ServerUnitDiePacket(std::string const& data);
	virtual ~ServerUnitDiePacket();

    uint32_t getUnitID();

    void        setUnitID(uint32_t);
};

std::ostream& operator<<(std::ostream& os, ServerUnitDiePacket const& packet);

#endif /* !SERVERUNITDIEPACKET_H_ */