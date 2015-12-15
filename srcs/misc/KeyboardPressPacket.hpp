#ifndef KEYBOARDPRESSPACKET_H_
# define KEYBOARDPRESSPACKET_H_

#include "APacket.hpp"

class KeyboardPressPacket : public APacket
{
public:
  enum keyEvent {
    UpPress = 0,
    UpRealease,
    DownPress,
    DownRealease,
    RightPress,
    RightRealease,
    LeftPress,
    LeftRealease,
    SpacePress,
    SpaceRelease
  };
  KeyboardPressPacket();
  KeyboardPressPacket(std::string const& data);
  virtual ~KeyboardPressPacket();
  void setKey(keyEvent);
  keyEvent getKey();

};

#endif /* !KEYBOARDPRESSPACKET_H_ */
