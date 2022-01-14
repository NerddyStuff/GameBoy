#include "cartridge.h"
#include "bus.h"



Cartridge::Cartridge(const std::string FileName)
{
	uint8_t MBCType;
	uint8_t RamSize;

	struct gHeader
	{
		uint8_t gTitle;			//	0x0134 - 0x 0143, Rom title, in ASCII UPPERCASE
		uint8_t gCGBFlag{0x0};	//	0x0143, GameBoy color flag, only the msb of 0x0143
		uint8_t gType;			//	0x0147, Cartridge Type
		uint8_t gRomSize;		//  0x0148, Size of the rom, and how many banks it has
		uint8_t gRamSize;		//	0x0149, Size of the cartridge rom, if it has any that is
		uint8_t gDestination;	//	0x014A, Describes if the rom is japanese, probably redundant
	} header;
	



	std::streampos size;
	std::ifstream file(FileName, std::ios::in | std::ios::binary | std::ios::ate);
	
	if (file.is_open())
	{
		size = file.tellg();
		int mSize = size;

		file.seekg(0, std::ios::beg);
		
		m_Rom = std::make_unique<uint8_t[]>(static_cast<size_t>(mSize));
		m_Ram = std::make_unique<uint8_t[]>(static_cast<size_t>(mSize));	//This is not staying like this, further changes will be made


		file.read(reinterpret_cast<char*>(m_Rom.get()), size);

		/* header.gTitle = m_Rom[0x0134];
		header.gCGBFlag = m_Rom[0x0143];
		header.gType = m_Rom[0x0147];
		header.gRomSize = m_Rom[0x0148];
		header.gRamSize = m_Rom[0x0149];
		header.gDestination = m_Rom[0x014A]; */
		
		MBCType = m_Rom.get()[0x0147];
		RamSize = m_Rom.get()[0x0149];
		
		if (mSize < 0x014F)
			printf("Rom is smaller than expected");
		
		switch (MBCType)
		{
		case ROMONLY:
			m_MemoryController = std::make_unique<NoMBC>();
			break;
		
		default:
			m_MemoryController = std::make_unique<NoMBC>();
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
	uint16_t mbcADDR = 0;
	
	if (m_MemoryController.get()->mbcRead(addr, mbcADDR))
	{
		data = m_Rom.get()[mbcADDR];

		return true;
	}
	
	
	return false;
}

bool Cartridge::c_Write(uint16_t addr, uint8_t data)
{
	uint16_t mbcADDR = 0;
	
	if (m_MemoryController.get()->mbcWrite(addr, mbcADDR))
	{
		m_Rom.get()[mbcADDR] = data;

		return true;
	}
	
	
	return false;
}
