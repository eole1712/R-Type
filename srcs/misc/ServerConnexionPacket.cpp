
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

bool	ServerConnexionPacket::getStatus() {
	return *reinterpret_cast<const bool*>(_data.substr(kHeaderSize, sizeof(bool)).c_str());
}

std::string	ServerConnexionPacket::getServerString() {
	return std::string(reinterpret_cast<const char*>(_data.substr(kHeaderSize + sizeof(bool), kServerStringSize).c_str()));
}

