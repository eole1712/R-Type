// #ifdef _WIN32
// #include "windows.h"
// #endif
#include "ISocket.hpp"
#include "UdpSocket.hpp"
#include "NetManager.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "ServerConnexionPacket.hpp"
#include "Thread.hpp"
#include "APacket.hpp"
#include "NetServer.hpp"

int main(int argc, char *argv[])
{
  NetServer* rec;
  NetManager* nm;

  if (argc != 2) {
    std::cout << "usage : ./server port_ecoute" << std::endl;
    return 1;
  }

  nm = new NetManager();
  rec = new NetServer(std::atoi(argv[1]), nm);
  std::function<void(std::nullptr_t)> fptr = [nm] (std::nullptr_t) {
    nm->loop();
  };
  Thread<std::nullptr_t> t(fptr, nullptr);
  t.join();
}
