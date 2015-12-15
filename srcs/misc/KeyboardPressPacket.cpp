#include "KeyboardPressPacket.hpp"

KeyboardPressPacket::KeyboardPressPacket()
  : APacket(5)
{
  ;
}

KeyboardPressPacket::KeyboardPressPacket(std::string const& data)
  : APacket(data)
{

}

void KeyboardPressPacket::setKey(KeyboardPressPacket::keyEvent event)
{
  _data.replace(kHeaderSize, sizeof(keyEvent), reinterpret_cast<const char*>(&event), sizeof(keyEvent));
}

KeyboardPressPacket::keyEvent KeyboardPressPacket::getKey()
{
  return *reinterpret_cast<const keyEvent*>(_data.substr(kHeaderSize, sizeof(keyEvent)).c_str());
}
