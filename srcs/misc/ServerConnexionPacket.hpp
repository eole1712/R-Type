
#ifndef SERVERCONNEXIONPACKET_H_
#define SERVERCONNEXIONPACKET_H_ 

#include "APacket.hpp"

// ||||||||||||||PACKETSIZE||||||||||||||||||
// IDPACKET||TYPEPACKET||STATUS||SRVSTRING|||

class ServerConnexionPacket : public APacket {
public:

	static constexpr int kServerStringSize = 100;

	ServerConnexionPacket();
	ServerConnexionPacket(std::string const& data);
	virtual ~ServerConnexionPacket();

	bool getStatus();
	std::string getServerString();

	void setStatus(bool status);
	void setServerString(std::string const& str);
};

#endif /* !SERVERCONNEXIONPACKET_H_ */