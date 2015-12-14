#include "NetServer.hpp"

NetServer::NetServer(int port, NetManager* manager)
  : Networker(port, manager)
{}

NetServer::~NetServer()
{}
