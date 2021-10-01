#include "bus.h"


Bus::Bus()
{
    m_Cpu.connectBus(this);
    m_Timer.connectTimer(this);
    
    for(auto &i : WRAM) i = 0x00;
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
        uint16_t mAddr = addr & 0x1FFF;
        VRAM[mAddr] = data;
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF)
    {
        cart.get()->m_Ram[addr] = data;
    }
    else if ((addr >= 0xC000 && addr <= 0xCFFF) || (addr >= 0xE000 && addr <= 0xFDFF))  //WRAM
    {
        uint16_t mAddr = addr & 0x0FFF;
        WRAM[mAddr] = data;
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
    {
        uint16_t mAddr = addr & 0x00FF;
        OAM[mAddr] = data;
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
        m_Cpu.m_EnableInt = data;
    }
    
}

uint8_t Bus::read(uint16_t addr)
{
    uint8_t data = 0x00;

    if (cart.get()->c_Read(addr, data))
    {    
        
    }
    else if (addr >= 0x8000 && addr <= 0x9FFF)
    {
        uint16_t mAddr = addr & 0x1FFF;
        data = VRAM[mAddr];
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF)
    {
        data = cart.get()->m_Ram[addr];
    }
    else if ((addr >= 0xC000 && addr <= 0xCFFF) || (addr >= 0xE000 && addr <= 0xFDFF))  //WRAM
    {
        uint16_t mAddr = addr & 0x0FFF;
        data = WRAM[mAddr];
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
    {
        uint16_t mAddr = addr & 0x00FF;
        data = OAM[mAddr];
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F)
    {
        
    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE)
    {
        
    }
    else if (addr == 0xFFFF)
    {
        data = m_Cpu.m_EnableInt;
    }
    
    return data;
}

void  Bus::InsertGame(std::shared_ptr<Cartridge> &Cartridge)
{
    this->cart = Cartridge;
}
void Bus::BusClock()
{
    m_Cpu.Clock();
    m_Timer.DivTick();
    m_Timer.TimaTick();
}
void Bus::BusReset()
{
    m_Cpu.ResetCpu();
}
