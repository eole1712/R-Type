
#ifndef CLIENTCONNEXIONPACKET_H_
#define CLIENTCONNEXIONPACKET_H_ 

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE||||||||||||||||||
// IDPACKET||TYPEPACKET||STATUS||SRVSTRING|||

class ClientConnexionPacket : public APacket {
public:

	static constexpr int kPlayerNameSize = 100;

	ClientConnexionPacket();
	ClientConnexionPacket(std::string const& data);
	virtual ~ClientConnexionPacket();

	std::string getClientName();

	void setClientName(std::string const& name);
};

#endif /* !CLIENTCONNEXIONPACKET_H_ */