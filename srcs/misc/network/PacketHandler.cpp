
#include "PacketHandler.hpp"

std::vector<std::function<void(APacket* packet, playerId id) > > PacketHandler::_packetHandlerFuncs = {
  [] (APacket* packet, playerId id) {
    ServerConnexionPacket* pack = dynamic_cast<ServerConnexionPacket*>(packet);
    if ()
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  },
  [] (APacket* packet, playerId id) {
    return ;
  }
};

PacketHandler::PacketHandler() {

}

PacketHandler::~PacketHandler() {

}

void		PacketHandler::handlePacket(APacket* packet, playerId id) {
	_packetHandlerFuncs[packet->getType()](packet, id);
}