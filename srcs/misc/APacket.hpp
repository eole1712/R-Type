#ifndef APACKET_H_
# define APACKET_H_

# include <cstdint>
# include <string>

// ||||||||||||||PACKETSIZE||||||||||||||||||
// IDPACKET||TYPEPACKET||||||||||||||||||||||

class APacket {
public:
  typedef uint16_t idSize;
  typedef uint8_t packetTypeSize;

  enum eType
    {
      SERVERCONNEXION,
      CLIENTCONNEXION,
      SERVERGAMEINFO,
      CLIENTGAMEINFO
    };

  static constexpr uint32_t kMaxPacketSize = 512;

  APacket(uint8_t type);
  APacket(std::string const& other);
  virtual ~APacket();

  uint16_t getId() const;
  uint8_t	getType() const;
  virtual std::string const& getData() const;
  static uint8_t sGetType(std::string const&);

  void setId(uint16_t id);
protected:
  std::string _data;
};

#endif /* !APACKET_H_ */
