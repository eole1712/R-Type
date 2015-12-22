#ifndef NETCLIENT_H_
# define NETCLIENT_H_

#include "APacket.hpp"
#include "Networker.hpp"

class NetClient : public Networker
{
public:
  NetClient(int port, NetManager*, IPacketHandler*);
  virtual ~NetClient();
  void connect(std::string const& addr, int port, std::string const& name);
  /*!
   * \param APacket* : ptr to the packet to be sent
   * \brief calls the parent send with id 0
   */
  void sendPacket(APacket*);
  int getCurrent();
  void setServer(int id);
private:
  int _current;
};


#endif /* !NETCLIENT_H_ */
