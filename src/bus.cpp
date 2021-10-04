#include "bus.h"

Bus::Bus()
{
    m_Cpu.connectBus(this);
    m_Timer.connectTimer(this);

    m_InputStatus = 0xCF;

    a_IOPorts[0x0F] = 0xE1;
    a_IOPorts[0x40] = 0x91;
    a_IOPorts[0x41] = 0x85;
    a_IOPorts[0x42] = 0x00;
    a_IOPorts[0x43] = 0x00;
    a_IOPorts[0x44] = 0x00;
    a_IOPorts[0x45] = 0x00;
    a_IOPorts[0x46] = 0xFF;
    a_IOPorts[0x47] = 0xFC;
    a_IOPorts[0x4A] = 0x00;
    a_IOPorts[0x4B] = 0x00;
    a_IOPorts[0x4D] = 0xFF;
    a_IOPorts[0x4F] = 0xFF;
    a_IOPorts[0x51] = 0xFF;
    a_IOPorts[0x52] = 0xFF;
    a_IOPorts[0x53] = 0xFF;
    a_IOPorts[0x54] = 0xFF;
    a_IOPorts[0x55] = 0xFF;
    a_IOPorts[0x56] = 0xFF;
    a_IOPorts[0x68] = 0xFF;
    a_IOPorts[0x69] = 0xFF;
    a_IOPorts[0x6A] = 0xFF;
    a_IOPorts[0x6B] = 0xFF;
    a_IOPorts[0x70] = 0xFF;

    for (auto &i : a_WRAM)
        i = 0x00;
};

Bus::~Bus(){
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
        a_VRAM[mAddr] = data;
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF)
    {
        cart.get()->m_Ram[addr] = data;
    }
    else if ((addr >= 0xC000 && addr <= 0xCFFF) || (addr >= 0xE000 && addr <= 0xFDFF)) //a_WRAM
    {
        uint16_t mAddr = addr & 0x0FFF;
        a_WRAM[mAddr] = data;
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
    {
        uint16_t mAddr = addr & 0x00FF;
        a_OAM[mAddr] = data;
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F)
    {
        if (addr == JOYPAD)
            m_InputStatus = data;
        if(addr == IE)
            m_IEFlag = data;

        a_IOPorts[(addr & 0x00FF)] = data;
    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE)
    {
        uint16_t mAddr = (addr & 0x00FF);
        a_HRAM[mAddr] = data;
    }
    else if (addr == 0xFFFF)
    {
        m_IEFlag = data;
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
        data = a_VRAM[mAddr];
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF)
    {
        data = cart.get()->m_Ram[addr];
    }
    else if ((addr >= 0xC000 && addr <= 0xCFFF) || (addr >= 0xE000 && addr <= 0xFDFF)) //a_WRAM
    {
        uint16_t mAddr = addr & 0x0FFF;
        data = a_WRAM[mAddr];
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F)
    {
        uint16_t mAddr = addr & 0x00FF;
        data = a_OAM[mAddr];
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F)
    {
        if (addr == JOYPAD)
            data = m_InputStatus;
        if (addr == IE)
            data = m_IEFlag;
        
        data = a_IOPorts[(addr & 0x00FF)];

    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE)
    {
        uint16_t mAddr = (addr & 0x00FF);
        data = a_HRAM[mAddr];
    }
    else if (addr == 0xFFFF)
    {
        data = m_IEFlag;
    }

    return data;
}

void Bus::InsertGame(std::shared_ptr<Cartridge> &Cartridge)
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
