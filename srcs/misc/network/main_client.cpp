#include "Networker.hpp"
#include "NetManager.hpp"
#include "NetClient.hpp"
#include "Thread.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <functional>

int main(int argc, char *argv[])
{
  NetClient* rec;
  NetManager* nm;

  if (argc != 4) {
    std::cout << "usage : ./client port_ecoute addr_envoi port_envoi" << std::endl;
    return 1;
  }

  nm = new NetManager;
  std::function<void(std::nullptr_t)> fptr = [nm] (std::nullptr_t) {
    nm->loop();
  };
  Thread<std::nullptr_t> t(fptr, nullptr);
  rec = new NetClient(std::atoi(argv[1]), nm);
  rec->connect(argv[2], std::atoi(argv[3]), "toto");
  rec->send(packet);
  t.join();
  return 0;
}
