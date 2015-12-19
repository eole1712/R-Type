#ifndef IGAMEHANDLER_H_
# define IGAMEHANDLER_H_

#include "ClientKeyboardPressPacket.hpp"

class Game;

class IGameHandler {
public:
virtual void sendKey(ClientKeyboardPressPacket::keyEvent) = 0;
  virtual void setGame(Game*) = 0;
};

#endif /* !IGAMEHANDLER_H_ */
