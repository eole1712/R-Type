#ifndef IMENUHANDLER_H_
# define IMENUHANDLER_H_

#include "IGameHandler.hpp"

class IMenuHandler
{
  public:
  virtual void selectGame(std::string const& name) = 0;
  virtual void connect(std::string const& ip, std::string const& name) = 0;
  virtual void refreshGames() = 0;
  virtual void createGame(std::string const& name) = 0;
  virtual void sendKey(ClientKeyboardPressPacket::keyEvent) = 0;
  virtual IGameHandler *getGameHandler() = 0;
};

#endif /* !IMENUHANDLER_H_ */
