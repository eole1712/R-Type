
#include "ServerUnitDiePacket.hpp"

ServerUnitDiePacket::ServerUnitDiePacket() : APacket(APacket::SERVERUNITDIE) {

}

ServerUnitDiePacket::ServerUnitDiePacket(std::string const& data) : APacket(data) {

}

ServerUnitDiePacket::~ServerUnitDiePacket() {};

uint32_t	ServerUnitDiePacket::getUnitID() {
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize, sizeof(uint32_t)).c_str());
}

void ServerUnitDiePacket::setUnitID(uint32_t id) {
    _data.replace(kHeaderSize,
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}
