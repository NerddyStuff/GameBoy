#include "cartridge.h"
#include "bus.h"

Cartridge::Cartridge(const std::string FileName)
{
	uint8_t MBCType;
	uint8_t RamSize;

	struct gHeader
	{
		// uint8_t gTitle;		   //	0x0134 - 0x 0143, Rom title, in ASCII UPPERCASE
		// uint8_t gCGBFlag	       //	0x0143, GameBoy color flag, only the msb of 0x0143
		uint8_t gType; //	0x0147, Cartridge Type
		// uint8_t gRomSize; //   0x0148, Size of the rom, and how many banks it has
		uint8_t gRamSize; //	0x0149, Size of the cartridge rom, if it has any
	} header;

	std::streampos size;
	std::ifstream file(FileName, std::ios::in | std::ios::binary | std::ios::ate);

	if (file.is_open())
	{
		size = file.tellg();
		int f_Size = size;

		file.seekg(0, std::ios::beg);

		m_Rom = std::make_unique<uint8_t[]>(static_cast<size_t>(f_Size));

		file.read(reinterpret_cast<char *>(m_Rom.get()), size);

		header.gType = m_Rom[0x0147];
		header.gRamSize = m_Rom[0x0149];

		if (f_Size < 0x014F)
			printf("Rom is smaller than expected");

		int RamSize;

		switch (header.gRamSize)
		{
		case NORAM:
			// Do nothing
			break;
		case RAM_8KB:
			RamSize = 0x2000;
			break;
		case RAM_32KB:
			RamSize = 0x8000;
			break;
		case RAM_128KB:
			RamSize = 0x20000;
			break;
		case RAM_64KB:
			RamSize = 0x10000;
		default:
			printf("Unknown RAM Size\n");
			break;
		}

		// Make MBC
		switch (header.gType)
		{
		case ROMONLY:
			m_MemoryController = std::make_unique<NoMBC>();
			break;
		case MBC1:
			m_MemoryController = std::make_unique<MBC_1>();
			m_MemoryController.get()->Set(header.gType);
			break;
		case MBC1_RAM:
			m_MemoryController = std::make_unique<MBC_1>();
			m_Ram = std::make_unique<uint8_t[]>(static_cast<size_t>(RamSize));
			m_MemoryController.get()->Set(header.gType);
			break;
		case MBC1_RAM_BATTERY:
			m_MemoryController = std::make_unique<MBC_1>();
			m_Ram = std::make_unique<uint8_t[]>(static_cast<size_t>(RamSize));
			m_MemoryController.get()->Set(header.gType);
			break;
		default:
			printf("MBC Unknown or not supported\n");
			std::cerr << "MBC id: " << header.gType << std::endl;
			std::exit(1);
			break;
		}
	}
	else
	{
		std::cerr << "Could not load ROM file\n";
		std::exit(1);
	}

	file.close();
}

Cartridge::~Cartridge()
{
}

bool Cartridge::c_Read(uint16_t addr, uint8_t &data)
{
	uint32_t mbcADDR = 0;

	if (m_MemoryController.get()->mbcRead(addr, mbcADDR))
	{
		data = m_Rom[mbcADDR];

		return true;
	}

	return false;
}

bool Cartridge::c_Write(uint16_t addr, uint8_t data)
{
	uint16_t mbcADDR = 0;

	if (m_MemoryController.get()->mbcWrite(addr, data, mbcADDR))
	{
		// m_Rom[mbcADDR] = data;

		return true;
	}

	return false;
}
