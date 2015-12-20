
#include "ClientGameConnectPacket.hpp"

ClientGameConnectPacket::ClientGameConnectPacket() : APacket(APacket::CLIENTGAMECONNECT) {

}

ClientGameConnectPacket::ClientGameConnectPacket(std::string const& data) : APacket(data) {

}

ClientGameConnectPacket::~ClientGameConnectPacket() {};

uint32_t	ClientGameConnectPacket::getRoomId() const{
	return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize, sizeof(uint32_t)).c_str());
}

std::string ClientGameConnectPacket::getRoomName() const{
	return std::string(reinterpret_cast<const char*>(_data.substr(kHeaderSize + sizeof(uint32_t), kRoomNameSize).c_str()));
}

void ClientGameConnectPacket::setRoomId(uint32_t id) {
	_data.replace(kHeaderSize,
		sizeof(uint32_t),
		reinterpret_cast<const char*>(&id),
		sizeof(uint32_t));
}

void ClientGameConnectPacket::setRoomName(std::string const& name) {
	_data.replace(kHeaderSize + sizeof(uint32_t),
		kRoomNameSize,
		name.c_str(),
		name.size());
}

std::ostream& operator<<(std::ostream& os, ClientGameConnectPacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", ROOMID : " << packet.getRoomId() << ", ROOMNAME : " << packet.getRoomName() << ".";
	return os;
}