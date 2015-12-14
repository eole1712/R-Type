#include "Networker.hpp"
#include "NetManager.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

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
  Networker* rec;
  NetManager* nm;

  if (argc != 2)
    return 1;

  nm = new NetManager;
  rec = new Networker(std::atoi(argv[1]), nm);

  nm->loop();
}
