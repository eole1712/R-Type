#ifndef KEYBOARDPRESSPACKET_H_
# define KEYBOARDPRESSPACKET_H_

#include "APacket.hpp"

class ClientKeyboardPressPacket : public APacket
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
    ClientKeyboardPressPacket();
    ClientKeyboardPressPacket(ClientKeyboardPressPacket::keyEvent event);
    ClientKeyboardPressPacket(std::string const& data);
    virtual ~ClientKeyboardPressPacket();
    void setKey(keyEvent);
    keyEvent getKey() const;
    std::pair<unsigned int, bool>   getStatus() const;
    
};

std::ostream& operator<<(std::ostream& os, ClientKeyboardPressPacket const& packet);

#endif /* !KEYBOARDPRESSPACKET_H_ */
