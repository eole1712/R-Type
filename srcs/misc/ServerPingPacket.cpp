
#include "ServerPingPacket.hpp"

ServerPingPacket::ServerPingPacket() : APacket(APacket::SERVERPING) {

}

ServerPingPacket::ServerPingPacket(std::string const& data) : APacket(data) {

}

ServerPingPacket::~ServerPingPacket() {};

bool	ServerPingPacket::getStatus() {
    return *reinterpret_cast<const bool*>(_data.substr(kHeaderSize, sizeof(bool)).c_str());
}

void ServerPingPacket::setStatus(bool id) {
    _data.replace(kHeaderSize,
                  sizeof(bool),
                  reinterpret_cast<const char*>(&id),
                  sizeof(bool));
}
