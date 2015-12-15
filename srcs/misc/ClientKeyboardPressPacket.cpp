#include "ClientKeyboardPressPacket.hpp"

ClientKeyboardPressPacket::ClientKeyboardPressPacket()
  : APacket(5)
{
  ;
}

ClientKeyboardPressPacket::ClientKeyboardPressPacket(std::string const& data)
  : APacket(data)
{

}

void ClientKeyboardPressPacket::setKey(ClientKeyboardPressPacket::keyEvent event)
{
  _data.replace(kHeaderSize, sizeof(keyEvent), reinterpret_cast<const char*>(&event), sizeof(keyEvent));
}

ClientKeyboardPressPacket::keyEvent ClientKeyboardPressPacket::getKey()
{
  return *reinterpret_cast<const keyEvent*>(_data.substr(kHeaderSize, sizeof(keyEvent)).c_str());
}

std::pair<unsigned int, bool>      ClientKeyboardPressPacket::getStatus()
{
    std::pair<unsigned int, bool>  pair;
    
    pair.first = getKey() / 2;
    pair.second = getKey() % 2;
    
    return pair;
}