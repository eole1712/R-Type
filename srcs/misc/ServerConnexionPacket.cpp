
#include "ServerConnexionPacket.hpp"

ServerConnexionPacket::ServerConnexionPacket() : APacket(APacket::SERVERCONNEXION) {

}

ServerConnexionPacket::ServerConnexionPacket(std::string const& data) : APacket(data) {

}

ServerConnexionPacket::~ServerConnexionPacket() {};

void	ServerConnexionPacket::setStatus(bool status) {
	_data.replace(kHeaderSize,
		sizeof(bool),
		reinterpret_cast<const char*>(&status),
		sizeof(bool));
}

void	ServerConnexionPacket::setServerString(std::string const& str) {
	_data.replace(kHeaderSize + sizeof(bool),
		kServerStringSize,
		str.c_str(),
		str.size());
}

bool	ServerConnexionPacket::getStatus() const{
	return *reinterpret_cast<const bool*>(_data.substr(kHeaderSize, sizeof(bool)).c_str());
}

std::string	ServerConnexionPacket::getServerString() const{
	return std::string(reinterpret_cast<const char*>(_data.substr(kHeaderSize + sizeof(bool), kServerStringSize).c_str()));
}

std::ostream& operator<<(std::ostream& os, ServerConnexionPacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", STATUS : " << (int)packet.getStatus() << ", SERVERSTRING : " << packet.getServerString() << ".";
	return os;
}