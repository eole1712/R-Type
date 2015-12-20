#ifndef NETMANAGER_H_
# define NETMANAGER_H_

#include <map>
#include <list>
// TODO use our threads
#include <mutex>
#if defined(_WIN32)
#include "Winsock2.h"
#endif
// #include <thread>
// end TOD

#include "../Lock.hpp"
#include "ISocket.hpp"
#include <tuple>

class NetManager
{
private:
  typedef std::list<std::tuple<std::string, ISocket::sendHandler, std::string, int> > sendList;

  typedef std::list<std::pair<std::string&, ISocket::receiveHandler> > receiveList;

  typedef Lock Mutex;
public:
  NetManager();
  virtual ~NetManager();
  static NetManager* getInstance();
  static void loopStart();
  void loop();
  void addSendCall(int sd, std::string, ISocket::sendHandler&, std::string addr, int port);
  void addReceiveCall(int sd, std::string&, ISocket::receiveHandler&);
  void addSocket(int sd, ISocket*);
  bool find(int sd);
  void deleteSocket(int sd);
private:
  template <typename T>
  void setFds(int& maxFd, fd_set& set)
  {
    ;
  }
  template <typename T>
  void doAction(fd_set &set, unsigned int timeout)
  {

  }
protected:
  static NetManager*		_ptr;
  ISocket::returnCode		_ret;
  unsigned int			_timeout;
  std::map<int, ISocket*>	_sockets;
  std::map<int, sendList>	_sendings;
  std::map<int, receiveList>	_reiceivings;
  Mutex				_mutex;
};

#endif /* !NETMANAGER_H_ */
