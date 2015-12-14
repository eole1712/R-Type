
#include "ServerConnexionPacket.hpp"

ServerConnexionPacket::ServerConnexionPacket() : APacket(APacket::SERVERCONNEXION) {

}

ServerConnexionPacket::ServerConnexionPacket(std::string const& data) : APacket(data) {

}

ServerConnexionPacket::~ServerConnexionPacket() {};

void	ServerConnexionPacket::setStatus(bool status) {
	_data.replace(sizeof(APacket::idSize) + sizeof(APacket::packetTypeSize),
			sizeof(bool),
			reinterpret_cast<const char*>(&status),
			sizeof(bool));
}

void	ServerConnexionPacket::setServerString(std::string const& str) {
	_data.replace(sizeof(APacket::idSize) + sizeof(APacket::packetTypeSize) + sizeof(bool),
			kServerStringSize,
			str.c_str(),
			kServerStringSize);
}

bool	ServerConnexionPacket::getStatus() {
	return *reinterpret_cast<const bool*>(_data.substr(sizeof(APacket::idSize) + sizeof(APacket::packetTypeSize), sizeof(bool)).c_str());
}

std::string	ServerConnexionPacket::getServerString() {
	return std::string(reinterpret_cast<const char*>(_data.substr(sizeof(APacket::idSize) + sizeof(APacket::packetTypeSize) + sizeof(bool), sizeof(kServerStringSize)).c_str()));
}

