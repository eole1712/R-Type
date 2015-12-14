#ifndef NETSERVER_H_
# define NETSERVER_H_

#include "Networker.hpp"

class NetServer : public Networker
{
public:
  NetServer(int port, NetManager*);
  virtual ~NetServer();

};

#endif /* !NETSERVER_H_ */
