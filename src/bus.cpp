#include "bus.h"


Bus::Bus()
{
    cpu.connectBus(this);
    
    for(auto &i : AddressBus) i = 0x00;
};

Bus::~Bus()
{
    //Does nothing
};

void Bus::write(uint16_t addr, uint8_t data)
{
    if (cart.get()->c_Write(addr, data))
    {

    }
    else if (addr >= 0x8000 && addr <= 0x9FFF)
    {
        /* code */
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF)
    {
        /* code */
    }
    else if (addr >= 0xC000 && addr <= 0xCFFF)  //WRAM
    {
        /* code */
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
    {
        /* code */
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F)
    {
        /* code */
    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE)
    {
        /* code */
    }
    else if (addr == 0xFFFF)
    {
        /* code */
    }
    
    
    
}

uint8_t Bus::read(uint16_t addr)
{
    uint8_t byte = 0x00;

    if (cart.get()->c_Read(addr, byte))
    {    
        
    }
    else if (addr >= 0x8000 && addr <= 0x9FFF)
    {
        
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF)
    {
        
    }
    else if (addr >= 0xC000 && addr <= 0xCFFF)  //WRAM
    {
        
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
    {
        
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F)
    {
        
    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE)
    {
        
    }
    else if (addr == 0xFFFF)
    {
        
    }
    
    return byte;
}

void  Bus::InsertGame(std::shared_ptr<Cartridge> &Cartridge)
{
    this->cart = Cartridge;
}

void Bus::BusClock()
{
    cpu.Clock();
}
void Bus::Reset()
{
    cpu.ResetCpu();
}
