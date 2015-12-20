
#include "ServerUnitSpawnPacket.hpp"

ServerUnitSpawnPacket::ServerUnitSpawnPacket() : APacket(APacket::SERVERUNITSPAWN) {

}

ServerUnitSpawnPacket::ServerUnitSpawnPacket(std::string const& data) : APacket(data) {

}

ServerUnitSpawnPacket::~ServerUnitSpawnPacket() {};

uint64_t	ServerUnitSpawnPacket::getTimer() const{
	return *reinterpret_cast<const uint64_t*>(_data.substr(kHeaderSize, sizeof(uint64_t)).c_str());
}

uint32_t	ServerUnitSpawnPacket::getX() const{
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize + sizeof(uint64_t), sizeof(uint32_t)).c_str());
}

uint32_t	ServerUnitSpawnPacket::getY() const{
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize + sizeof(uint64_t) + (1 * sizeof(uint32_t)), sizeof(uint32_t)).c_str());
}

uint32_t	ServerUnitSpawnPacket::getUnitType() const{
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize + sizeof(uint64_t) + (2 * sizeof(uint32_t)), sizeof(uint32_t)).c_str());
}

uint32_t	ServerUnitSpawnPacket::getUnitID() const{
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize + sizeof(uint64_t) + (3 * sizeof(uint32_t)), sizeof(uint32_t)).c_str());
}

float       ServerUnitSpawnPacket::getParam() const{
    return *reinterpret_cast<const float*>(_data.substr(kHeaderSize + sizeof(uint64_t) + (4 * sizeof(uint32_t)), sizeof(float)).c_str());
}

void ServerUnitSpawnPacket::setTimer(uint64_t id) {
	_data.replace(kHeaderSize,
		sizeof(uint64_t),
		reinterpret_cast<const char*>(&id),
		sizeof(uint64_t));
}

void ServerUnitSpawnPacket::setX(uint32_t id) {
    _data.replace(kHeaderSize + sizeof(uint64_t),
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}

void ServerUnitSpawnPacket::setY(uint32_t id) {
    _data.replace(kHeaderSize + sizeof(uint64_t) + (1 * sizeof(uint32_t)),
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}

void ServerUnitSpawnPacket::setUnitType(uint32_t id) {
    _data.replace(kHeaderSize + sizeof(uint64_t) + (2 * sizeof(uint32_t)),
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}

void ServerUnitSpawnPacket::setUnitID(uint32_t id) {
    _data.replace(kHeaderSize + sizeof(uint64_t) + (3 * sizeof(uint32_t)),
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}

void ServerUnitSpawnPacket::setParam(float id) {
    _data.replace(kHeaderSize + sizeof(uint64_t) + (4 * sizeof(uint32_t)),
                  sizeof(float),
                  reinterpret_cast<const char*>(&id),
                  sizeof(float));
}

std::ostream& operator<<(std::ostream& os, ServerUnitSpawnPacket const& packet) {
  os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", TIMER : " << packet.getTimer() << ", X : " << packet.getX() << ", Y : " << packet.getY() << ", UNITTYPE : " << packet.getUnitType() << ", UNITID : " << packet.getUnitID() << ", PARAM : " << packet.getParam() << ".";
  return os;
}