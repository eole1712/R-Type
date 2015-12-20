
#include "ServerUnitDiePacket.hpp"

ServerUnitDiePacket::ServerUnitDiePacket() : APacket(APacket::SERVERUNITDIE) {

}

ServerUnitDiePacket::ServerUnitDiePacket(std::string const& data) : APacket(data) {

}

ServerUnitDiePacket::~ServerUnitDiePacket() {};

uint32_t	ServerUnitDiePacket::getUnitID() const{
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize, sizeof(uint32_t)).c_str());
}

void ServerUnitDiePacket::setUnitID(uint32_t id) {
    _data.replace(kHeaderSize,
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}

std::ostream& operator<<(std::ostream& os, ServerUnitDiePacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", UNITID : " << packet.getUnitID()<< ".";
	return os;
}