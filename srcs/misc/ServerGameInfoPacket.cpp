
#include "ServerGameInfoPacket.hpp"

ServerGameInfoPacket::ServerGameInfoPacket() : APacket(APacket::SERVERGAMEINFO) {

}

ServerGameInfoPacket::ServerGameInfoPacket(std::string const& data) : APacket(data) {

}

ServerGameInfoPacket::~ServerGameInfoPacket() {};

uint32_t	ServerGameInfoPacket::getRoomId() const{
	return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize, sizeof(uint32_t)).c_str());
}

uint8_t ServerGameInfoPacket::getRoomSlots() const{
	return *reinterpret_cast<const uint8_t*>(_data.substr(kHeaderSize + sizeof(uint32_t), sizeof(uint8_t)).c_str());
}

uint8_t ServerGameInfoPacket::getRoomReady() const{
    return *reinterpret_cast<const uint8_t*>(_data.substr(kHeaderSize + sizeof(uint32_t) + sizeof(uint8_t), sizeof(uint8_t)).c_str());
}

std::string ServerGameInfoPacket::getRoomName() const{
	return std::string(reinterpret_cast<const char*>(_data.substr(kHeaderSize + sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint8_t), kRoomNameSize).c_str()));
}

void ServerGameInfoPacket::setRoomId(uint32_t id) {
	_data.replace(kHeaderSize,
		sizeof(uint32_t),
		reinterpret_cast<const char*>(&id),
		sizeof(uint32_t));
}

void ServerGameInfoPacket::setRoomSlots(uint8_t nb) {
	_data.replace(kHeaderSize + sizeof(uint32_t),
		sizeof(uint8_t),
		reinterpret_cast<const char*>(&nb),
		sizeof(uint8_t));
}

void ServerGameInfoPacket::setRoomReady(uint8_t nb) {
    _data.replace(kHeaderSize + sizeof(uint32_t) + sizeof(uint8_t),
                  sizeof(uint8_t),
                  reinterpret_cast<const char*>(&nb),
                  sizeof(uint8_t));
}


void ServerGameInfoPacket::setRoomName(std::string const& name) {
	_data.replace(kHeaderSize + sizeof(uint32_t) + sizeof(uint8_t) + sizeof(uint8_t),
		kRoomNameSize,
		name.c_str(),
		name.size());
}

std::ostream& operator<<(std::ostream& os, ServerGameInfoPacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", ROOMID : " << packet.getRoomId() << ", ROOMSLOTS : " << (int)packet.getRoomSlots() << ", ROOMREADY : " << (int)packet.getRoomReady() << ", ROOMNAME : " << packet.getRoomName() << ".";
	return os;
}