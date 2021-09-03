#include "bus.h"


Bus::Bus()
{
    for(auto i : AddressBus)
    {
        AddressBus[i] = 0x0;
    }
    cpu.connectBus(this);
    game.connectCartridge(this);
};

Bus::~Bus()
{
    //Does nothing
};

void Bus::write(uint16_t addr, uint8_t data)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        AddressBus[addr] = data;

}

uint8_t Bus::read(uint16_t addr)
{
    if (addr >= 0x0000 && addr <= 0xFFFF)
        return AddressBus[addr];

    return 0x00;
}