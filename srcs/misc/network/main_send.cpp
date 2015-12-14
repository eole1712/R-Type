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
#include "Thread.hpp"
#include "APacket.hpp"

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
  std::function<void(std::nullptr_t)> fptr = [nm] (std::nullptr_t) {
    nm->loop();
  };
  Thread<std::nullptr_t> t(fptr, nullptr);
  while (42)
    {
      APacket pack(id % 4);
      std::string msg = pack.getData();
      sock->async_send(msg, [] (ISocket::returnCode ret, size_t ret_size) {
	if (ret == ISocket::Fail)
	  std::cout << "send failed" << std::endl;
	else
	  std::cout << "msg sent with size : " << ret_size << std::endl;
      });
      ++id;
      #ifdef _WIN32
      Sleep(5);
      #else
      usleep(5000);
      #endif
    }
  t.join();
}
