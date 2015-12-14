
#include "ClientGameInfoPacket.hpp"

ClientGameInfoPacket::ClientGameInfoPacket() : APacket(APacket::CLIENTGAMEINFO) {

}

ClientGameInfoPacket::ClientGameInfoPacket(std::string const& data) : APacket(data) {

}

ClientGameInfoPacket::~ClientGameInfoPacket() {};