
#include "ServerGameConnectPacket.hpp"

ServerGameConnectPacket::ServerGameConnectPacket() : APacket(APacket::SERVERGAMECONNECT) {

}

ServerGameConnectPacket::ServerGameConnectPacket(std::string const& data) : APacket(data) {

}

ServerGameConnectPacket::~ServerGameConnectPacket() {};

void	ServerGameConnectPacket::setStatus(bool status) {
	_data.replace(kHeaderSize,
		sizeof(bool),
		reinterpret_cast<const char*>(&status),
		sizeof(bool));
}

void	ServerGameConnectPacket::setPlayerId(uint8_t id) {
	_data.replace(kHeaderSize + sizeof(bool),
		sizeof(uint8_t),
		reinterpret_cast<const char*>(&id),
		sizeof(uint8_t));
}

void	ServerGameConnectPacket::setGameId(uint32_t id) {
	_data.replace(kHeaderSize + sizeof(bool) + sizeof(uint8_t),
		sizeof(uint32_t),
		reinterpret_cast<const char*>(&id),
		sizeof(uint32_t));
}

bool	ServerGameConnectPacket::getStatus() const{
	return *reinterpret_cast<const bool*>(_data.substr(kHeaderSize, sizeof(bool)).c_str());
}

uint8_t ServerGameConnectPacket::getPlayerId() const{
	return *reinterpret_cast<const uint8_t*>(_data.substr(kHeaderSize + sizeof(bool), sizeof(uint8_t)).c_str());
}

uint32_t ServerGameConnectPacket::getGameId() const{
	return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize + sizeof(bool) + sizeof(uint8_t), sizeof(uint32_t)).c_str());
}

std::ostream& operator<<(std::ostream& os, ServerGameConnectPacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", STATUS : " << packet.getStatus() << ", PLAYERID : " << packet.getPlayerId() << ", GAMEID : " << packet.getGameId() << ".";
	return os;
}