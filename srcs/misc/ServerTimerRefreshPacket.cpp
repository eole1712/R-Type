
#include "ServerTimerRefreshPacket.hpp"

ServerTimerRefreshPacket::ServerTimerRefreshPacket() : APacket(APacket::SERVERTIMERREFRESH) {

}

ServerTimerRefreshPacket::ServerTimerRefreshPacket(std::string const& data) : APacket(data) {

}

ServerTimerRefreshPacket::~ServerTimerRefreshPacket() {};

uint64_t	ServerTimerRefreshPacket::getCurrentTimer() {
    return *reinterpret_cast<const uint64_t*>(_data.substr(kHeaderSize, sizeof(uint64_t)).c_str());
}

void ServerTimerRefreshPacket::setCurrentTimer(uint64_t id) {
    _data.replace(kHeaderSize,
                  sizeof(uint64_t),
                  reinterpret_cast<const char*>(&id),
                  sizeof(uint64_t));
}

std::ostream& operator<<(std::ostream& os, ServerTimerRefreshPacket const& packet) {
	os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", CURRENTTIMER : " << packet.getCurrentTimer() << ".";
	return os;
}