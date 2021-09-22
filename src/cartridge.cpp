#include "cartridge.h"
#include "bus.h"



Cartridge::Cartridge(const std::string FileName)
{

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
	std::ifstream file(FileName, std::ios::ate | std::ios::binary | std::ios::in);
	
	if (file.is_open())
	{
		size = file.tellg();
		int32_t mSize = size;

		file.seekg(0, std::ios::beg);
		
		m_Rom = std::unique_ptr<uint8_t>(new uint8_t [static_cast<unsigned int>(mSize)]);

		file.read(reinterpret_cast<char*>(m_Rom.get()), mSize);

		/* header.gTitle = m_Rom[0x0134];
		header.gCGBFlag = m_Rom[0x0143];
		header.gType = m_Rom[0x0147];
		header.gRomSize = m_Rom[0x0148];
		header.gRamSize = m_Rom[0x0149];
		header.gDestination = m_Rom[0x014A]; */
		
		MBCType = m_Rom.get()[0x0147];
		
		if (mSize < 0x014F)
			printf("Rom is smaller than expected");
		
		switch (MBCType)
		{
		case ROMONLY:
			m_MemoryController = std::unique_ptr<NoMBC>(new NoMBC());
			break;
		
		default:
			m_MemoryController = std::unique_ptr<NoMBC>(new NoMBC());
			break;
		}
	}
	else
	{
		printf("Could not load ROM file");
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
		data = m_Rom.get()[mbcADDR];

		return true;
	}
	
	
	return false;
}

bool Cartridge::c_Write(uint16_t addr, uint8_t data)
{
	uint32_t mbcADDR = 0;
	
	if (m_MemoryController.get()->mbcWrite(addr, mbcADDR))
	{
		m_Rom.get()[mbcADDR] = data;

		return true;
	}
	
	
	return false;
}
