#include "cartridge.h"
#include "bus.h"


uint8_t Cartridge::read(uint16_t addr)
{
    return bus->read(addr);
}

void Cartridge::write(uint16_t addr, uint8_t data)
{
    bus->write(addr, data);
}

void Cartridge::LoadRom(char const* filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        std::streampos size = file.tellg();
		file.seekg(0, std::ios::beg);
		uint8_t* buffer = new uint8_t[(size)];
		file.read(reinterpret_cast<char*>(&buffer), size);
		file.close();

        for (uint16_t i = 0; i < size; i++)
        {
            write(i, *buffer);
        }
                
    }
    
}