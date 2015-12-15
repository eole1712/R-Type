
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

	uint64_t getTimer();
	uint32_t getX();
    uint32_t getY();
    uint32_t getUnitType();
    uint32_t getUnitID();
    float    getParam();

    void        setTimer(uint64_t);
    void        setX(uint32_t);
    void        setY(uint32_t);
    void        setUnitType(uint32_t);
    void        setUnitID(uint32_t);
    void        setParam(float);
};

#endif /* !SERVERUNITSPAWNPACKET_H_ */