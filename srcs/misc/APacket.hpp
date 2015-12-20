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
		SERVERCONNEXION = 0,
		SERVERGAMEINFO,
		SERVERGAMECONNECT,
        SERVERPLAYERMOVE,
        SERVERPING,
        SERVERUNITSPAWN,
        SERVERUNITDIE,
        SERVERTIMERREFRESH,
        CLIENTCONNEXION,
        CLIENTGAMEINFO,
	CLIENTGAMECONNECT,
	CLIENTGAMEKEY	    
	};

	static constexpr int kMaxPacketSize = 512;
	static constexpr int kHeaderSize = sizeof(idSize) + sizeof(packetTypeSize);
    static const int kNbServerPackets = 8;

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

std::ostream& operator<<(std::ostream& os, APacket const& packet);

#endif /* !APACKET_H_ */
