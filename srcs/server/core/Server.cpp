#include "ClientConnexionPacket.hpp"
#include "ClientGameInfoPacket.hpp"
#include "ClientGameConnectPacket.hpp"
#include "Thread.hpp"
#include "Server.hpp"

std::vector<std::function<void(APacket* packet, unsigned int id) > > Server::_packetHandlerFuncs = {
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
	std::function<void(std::nullptr_t)> fptr = [this] (std::nullptr_t) {
		_netManager->loop();
	};
	Thread<std::nullptr_t> t(fptr, nullptr);
}

void		Server::handlePacket(APacket* packet, unsigned int id) {
	_packetHandlerFuncs[packet->getType() - APacket::kNbServerPackets](packet, id);
}