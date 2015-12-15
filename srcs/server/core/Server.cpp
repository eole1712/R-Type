
#include "Server.hpp"

std::vector<std::function<void(APacket* packet, playerId id) > > Server::_packetHandlerFuncs = {
	[] (APacket* packet, unsigned int id) {
		ClientConnexionPacket* pack = dynamic_cast<ClientConnexionPacket*>(packet);
		if (pack == NULL)
			return;
	},
	[] (APacket* packet, unsigned int id) {
		ClientGameInfoPacket* pack = dynamic_cast<ClientGameInfoPacket*>(packet);
		if (pack == NULL)
			return;
	},
	[] (APacket* packet, unsigned int id) {
		ClientGameConnectPacket* pack = dynamic_cast<ClientGameConnectPacket*>(packet);
		if (pack == NULL)
			return;
	}
};


Server::Server() {
	_netManager = new NetManager();
	_netServer = new NetServer(kPort, _netManager, this);
}

Server::~Server() {
	delete _netServer;
	delete _netManager;
}

void	Server::start() {
	std::function<void(std::nullptr_t)> fptr = [nm] (std::nullptr_t) {
		nm->loop();
	};
	Thread<std::nullptr_t> t(fptr, nullptr);
}

void		Server::handlePacket(APacket* packet, unsigned int id) {
	_packetHandlerFuncs[packet->getType() - APacket::kNbServerPackets](packet, id);
}