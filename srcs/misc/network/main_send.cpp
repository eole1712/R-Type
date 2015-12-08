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
#include <thread>

int main(int argc, char *argv[])
{
  UdpSocket* sock;
  NetManager* nm;

  if (argc != 4)
    return 1;

  unsigned short id = 0;
  nm = new NetManager();
  sock = new UdpSocket(std::atoi(argv[2]), argv[1], nm);
  sock->setSendPort(atoi(argv[3]));
  std::ofstream os;

  os.open("send.txt");
  std::thread t([nm] {
    nm->loop();
  });
  while (42)
    {
      std::stringstream ss;
      ss << id;
      std::string msg = std::string(reinterpret_cast<char*>(&id), 2) + "Coucou" + ss.str();
      sock->async_send(msg, [] (ISocket::returnCode ret, size_t ret_size) {
	if (ret == ISocket::Fail)
	  std::cout << "send failed" << std::endl;
	else
	  std::cout << "msg sent with size : " << ret_size << std::endl;
      });
      ++id;
      os << "id : " << id << std::endl;
      sleep(0.005);
    }
  t.join();
}
