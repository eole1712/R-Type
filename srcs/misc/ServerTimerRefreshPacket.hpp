
#ifndef SERVERTIMERREFRESHPACKET_H_
#define SERVERTIMERREFRESHPACKET_H_

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE|||||||||||||
// IDPACKET||TYPEPACKET||CURRENT TIMER||

class ServerTimerRefreshPacket : public APacket {
public:

	ServerTimerRefreshPacket();
	ServerTimerRefreshPacket(std::string const& data);
	virtual ~ServerTimerRefreshPacket();

    uint64_t getCurrentTimer();

    void        setCurrentTimer(uint64_t);
};

std::ostream& operator<<(std::ostream& os, ServerTimerRefreshPacket const& packet);

#endif /* !SERVERTIMERREFRESHPACKET_H_ */