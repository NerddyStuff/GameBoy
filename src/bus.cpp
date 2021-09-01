#include "bus.h"


Bus::Bus()
{
    for(uint8_t i = 0; i < 65536; i++)
    {
        Addresses[i] = 0x0;
    }
    cpu.connectBus(this);
};

Bus::~Bus()
{
    //Does nothing
};

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        Addresses[addr] = data;

}

uint8_t Bus::read(uint16_t addr)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        return Addresses[addr];

    return 0x00;
}