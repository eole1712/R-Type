
#include "ServerPlayerMovePacket.hpp"

ServerPlayerMovePacket::ServerPlayerMovePacket() : APacket(APacket::SERVERPLAYERMOVE) {

}

ServerPlayerMovePacket::ServerPlayerMovePacket(std::string const& data) : APacket(data) {

}

ServerPlayerMovePacket::~ServerPlayerMovePacket() {};

uint32_t	ServerPlayerMovePacket::getPlayerID() {
	return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize, sizeof(uint32_t)).c_str());
}

uint32_t	ServerPlayerMovePacket::getX() {
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize + sizeof(uint32_t), sizeof(uint32_t)).c_str());
}

uint32_t	ServerPlayerMovePacket::getY() {
    return *reinterpret_cast<const uint32_t*>(_data.substr(kHeaderSize + (2 * sizeof(uint32_t)), sizeof(uint32_t)).c_str());
}

void ServerPlayerMovePacket::setPlayerID(uint32_t id) {
	_data.replace(kHeaderSize,
		sizeof(uint32_t),
		reinterpret_cast<const char*>(&id),
		sizeof(uint32_t));
}

void ServerPlayerMovePacket::setX(uint32_t id) {
    _data.replace(kHeaderSize + sizeof(uint32_t),
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}

void ServerPlayerMovePacket::setY(uint32_t id) {
    _data.replace(kHeaderSize + (2 * sizeof(uint32_t)),
                  sizeof(uint32_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint32_t));
}