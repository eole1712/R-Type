#include "ISocket.hpp"
#include "UdpSocket.hpp"
#include "NetManager.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>

static const int header_size = 2;

void handle_receive(UdpSocket* sock, std::string& data)
{
  sock->async_receive(data, [sock, &data] (ISocket::returnCode retCode, size_t ret, std::string addr, int port) {
    unsigned short id;

    std::cout << "size : " << ret << std::endl;
    std::string msg = std::string(data.c_str() + header_size, ret - header_size);

    id = *reinterpret_cast<const unsigned short*>(data.c_str());

    std::cout << "data received : " << msg << " of size : " << ret << " from " << addr << ":" << port << " with id : " << id << std::endl;

    //of << "id : " << id << std::endl;
    handle_receive(sock, data);
  });
}

int main(int argc, char *argv[])
{
  UdpSocket* sock;
  NetManager* nm;

  if (argc != 3)
    return 1;

  nm = new NetManager;
  sock = new UdpSocket(std::atoi(argv[2]), argv[1], nm);

  std::cout << "yolo" << std::endl;
  std::string data = "lol";
  data.resize(UdpSocket::bufferSize);
  std::cout << "init passed" << std::endl;
  std::ofstream of;

  of.open("log.txt");

  handle_receive(sock, data);
  nm->loop();
}
