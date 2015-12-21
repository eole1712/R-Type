
#ifndef SERVERUNITSPAWNPACKET_H_
#define SERVERUNITSPAWNPACKET_H_

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE|||||||||||||||||||||||||||||||||||||||||
// IDPACKET||TYPEPACKET||TIME SPAWN||X||Y||UNIT TYPE||UNIT ID||PARAM

class ServerUnitSpawnPacket : public APacket {
public:

	ServerUnitSpawnPacket();
	ServerUnitSpawnPacket(std::string const& data);
	virtual ~ServerUnitSpawnPacket();

	uint64_t getTimer() const;
	uint32_t getX() const;
    uint32_t getY() const;
    uint32_t getUnitType() const;
    uint32_t getUnitID() const;
    int      getParam() const;

    void        setTimer(uint64_t);
    void        setX(uint32_t);
    void        setY(uint32_t);
    void        setUnitType(uint32_t);
    void        setUnitID(uint32_t);
    void        setParam(int);
};

std::ostream& operator<<(std::ostream& os, ServerUnitSpawnPacket const& packet);

#endif /* !SERVERUNITSPAWNPACKET_H_ */