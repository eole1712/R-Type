#ifndef APACKET_H_
# define APACKET_H_

class APacket {
public:
	typedef uint16_t idSize;
	typedef uint8_t packetTypeSize;

	static constexpr uint32_t kMaxSize = 512;

	APacket(uint8_t type);
	APacket(std::string const& other);
	virtual ~APacket();

	uint16_t getId() const;
	uint8_t	getType() const;
	virtual std::string const& getData() const;

	void setId(uint16_t id);
private:
	std::string _data;
};

#endif /* !APACKET_H_ */