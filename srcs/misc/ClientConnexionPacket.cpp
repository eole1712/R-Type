

#include "ClientConnexionPacket.hpp"

ClientConnexionPacket::ClientConnexionPacket() : APacket(APacket::CLIENTCONNEXION) {

}

ClientConnexionPacket::ClientConnexionPacket(std::string const& data) : APacket(data) {

}

ClientConnexionPacket::~ClientConnexionPacket() {};

void	ClientConnexionPacket::setClientName(std::string const& str) {
	_data.replace(kHeaderSize,
		kPlayerNameSize,
		str.c_str(),
		str.size());
}

std::string	ClientConnexionPacket::getClientName() {
	return std::string(reinterpret_cast<const char*>(_data.substr(kHeaderSize, kPlayerNameSize).c_str()));
}

std::ostream& operator<<(std::ostream& os, ClientConnexionPacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", CLIENTNAME : " << packet.getClientName() << ".";
	return os;
}
