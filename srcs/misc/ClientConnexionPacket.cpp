
#include "ClientConnexionPacket.hpp"

ClientConnexionPacket::ClientConnexionPacket() : APacket(APacket::CLIENTCONNEXION) {

}

ClientConnexionPacket::ClientConnexionPacket(std::string const& data) : APacket(data) {

}

ClientConnexionPacket::~ClientConnexionPacket() {};

void	ClientConnexionPacket::setClientName(std::string const& str) {
	_data.replace(sizeof(APacket::idSize) + sizeof(APacket::packetTypeSize),
		kPlayerNameSize,
		str.c_str(),
		kPlayerNameSize);
}

std::string	ClientConnexionPacket::getClientName() {
	return std::string(reinterpret_cast<const char*>(_data.substr(kHeaderSize, kPlayerNameSize).c_str()));
}