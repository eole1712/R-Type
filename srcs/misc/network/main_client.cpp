#include "Networker.hpp"
#include "NetManager.hpp"
#include "NetClient.hpp"
#include "Thread.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <functional>

// static const int header_size = 2;

// void handle_receive(UdpSocket* sock, std::string& data)
// {
//   sock->async_receive(data, [sock, &data] (ISocket::returnCode retCode, size_t ret, std::string addr, int port) {
//     unsigned short id;

//     std::cout << "size : " << ret << std::endl;
//     std::string msg = std::string(data.c_str() + header_size, ret - header_size);

//     id = *reinterpret_cast<const unsigned short*>(data.c_str());

//     std::cout << "data received : " << msg << " of size : " << ret << " from " << addr << ":" << port << " with id : " << id << std::endl;

//     //of << "id : " << id << std::endl;
//     handle_receive(sock, data);
//   });
// }

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
  t.join();
  return 0;
}
