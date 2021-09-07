#include "cartridge.h"
#include "bus.h"



Cartridge::Cartridge()
{

}
Cartridge::~Cartridge()
{
    
}



void Cartridge::LoadRom(char const* filename)
{
    std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

    if (file.is_open())
	{
		std::streampos size = file.tellg();
		char* buffer = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(buffer, size);
		file.close();

		for (long i = 0; i < size; i++)
		{
            bus->write(i, buffer[i]);
		}

		delete[] buffer;
	}
    
}