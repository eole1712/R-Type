
#ifndef CLIENTCONNEXIONPACKET_H_
#define CLIENTCONNEXIONPACKET_H_ 

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE||||||||||||||||||
// IDPACKET||TYPEPACKET||STATUS||SRVSTRING|||

class ClientConnexionPacket : public APacket {
public:

	static constexpr int kPlayerNameSize = 16;

	ClientConnexionPacket();
	ClientConnexionPacket(std::string const& data);
	virtual ~ClientConnexionPacket();

	std::string getClientName() const;

	void setClientName(std::string const& name);
};

std::ostream& operator<<(std::ostream& os, ClientConnexionPacket const& packet);

#endif /* !CLIENTCONNEXIONPACKET_H_ */