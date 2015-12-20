#include "ClientKeyboardPressPacket.hpp"

ClientKeyboardPressPacket::ClientKeyboardPressPacket()
  : APacket(CLIENTGAMEKEY)
{
  ;
}

ClientKeyboardPressPacket::ClientKeyboardPressPacket(ClientKeyboardPressPacket::keyEvent event)
  : APacket(CLIENTGAMEKEY)
{
  _data.replace(kHeaderSize, sizeof(keyEvent), reinterpret_cast<const char*>(&event), sizeof(keyEvent));
}

ClientKeyboardPressPacket::ClientKeyboardPressPacket(std::string const& data)
  : APacket(data)
{

}

ClientKeyboardPressPacket::~ClientKeyboardPressPacket()
{
}

void ClientKeyboardPressPacket::setKey(ClientKeyboardPressPacket::keyEvent event)
{
  _data.replace(kHeaderSize, sizeof(keyEvent), reinterpret_cast<const char*>(&event), sizeof(keyEvent));
}

ClientKeyboardPressPacket::keyEvent ClientKeyboardPressPacket::getKey() const
{
  return *reinterpret_cast<const keyEvent*>(_data.substr(kHeaderSize, sizeof(keyEvent)).c_str());
}

std::pair<unsigned int, bool>      ClientKeyboardPressPacket::getStatus() const
{
    std::pair<unsigned int, bool>  pair;
    
    pair.first = getKey() / 2;
    pair.second = !(static_cast<bool>(getKey() % 2));
    
    return pair;
}

std::ostream& operator<<(std::ostream& os, ClientKeyboardPressPacket const& packet) {
  os << "ID : " << (int)packet.getId() << ", TYPE : " << (int)packet.getType() << ", KEY : " << packet.getStatus().first << ", PRESSED : " << (int)packet.getStatus().second << ".";
  return os;
}