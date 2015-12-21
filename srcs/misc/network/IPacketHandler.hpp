
#ifndef IPACKETHANDLER_H_
#define IPACKETHANDLER_H_

#include "APacket.hpp"

class IPacketHandler {
public:
  virtual ~IPacketHandler() {};

  virtual void handlePacket(APacket* packet, unsigned int id) = 0;
  virtual void disconnectPlayer(unsigned int id) = 0;
};

#endif /* !IPACKETHANDLER_H_ */
