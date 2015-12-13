
	APacket::APacket(uint8_t type) {
		_data.resize(kMaxSize);
		_data.replace(sizeof(APacket::idSize),
			sizeof(APacket::packetTypeSize),
			reinterpret_cast<const char*>(&type),
			sizeof(APacket::packetTypeSize));
	}

	APacket::APacket(std::string const& other) : _data(other) {

	}

	APacket::~APacket() {

	}

	APacket::idType APacket::getId() const {
		return *reinterpret_cast<APacket::idSize*>(_data.substr(0, sizeof(APacket::idSize)).c_str());
	}
	
	uint8_t	APacket::getType() const {
		return *reinterpret_cast<APacket::packetTypeSize*>(_data.substr(sizeof(APacket::idSize), sizeof(APacket::packetTypeSize)).c_str());
	}

	std::string const& APacket::getData() const {
		return _data;
	}

	void APacket::setId(APacket::idSize id) {
		_data.replace(0,
			sizeof(APacket::idSize),
			reinterpret_cast<const char*>(&id),
			sizeof(APacket::idSize));
	}