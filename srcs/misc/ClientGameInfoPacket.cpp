
#include "ClientGameInfoPacket.hpp"

ClientGameInfoPacket::ClientGameInfoPacket() : APacket(APacket::CLIENTGAMEINFO) {

}

ClientGameInfoPacket::ClientGameInfoPacket(std::string const& data) : APacket(data) {

}

ClientGameInfoPacket::~ClientGameInfoPacket() {};

std::ostream& operator<<(std::ostream& os, ClientGameInfoPacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ".";
	return os;
}