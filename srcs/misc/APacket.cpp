#include "APacket.hpp"

APacket::APacket(uint8_t type) {

	_data.resize(kMaxPacketSize, 0);
	_data.replace(sizeof(APacket::idSize),
		sizeof(APacket::packetTypeSize),
		reinterpret_cast<const char*>(&type),
		sizeof(APacket::packetTypeSize));
}

APacket::APacket(std::string const& other) : _data(other) {
	
}

APacket::~APacket() {

}

APacket::idSize APacket::getId() const {
	return *reinterpret_cast<const APacket::idSize*>(_data.substr(0, sizeof(APacket::idSize)).c_str());
}

uint8_t	APacket::getType() const {
	return sGetType(_data);
}

std::string const& APacket::getData() const {
	return _data;
}

void APacket::setId(APacket::idSize id) {
	_data.replace(0,
		sizeof(APacket::idSize),
		reinterpret_cast<const char*>(&id),
		sizeof(APacket::idSize));
}

uint8_t APacket::sGetType(const std::string &data) {
	return *reinterpret_cast<const APacket::packetTypeSize*>(data.substr(sizeof(APacket::idSize), sizeof(APacket::packetTypeSize)).c_str());
}

std::ostream& operator<<(std::ostream& os, APacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ".";
	return os;
}
