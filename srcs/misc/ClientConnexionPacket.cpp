

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
