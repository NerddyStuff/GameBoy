#include "bus.h"

Bus::Bus()
{
    m_Cpu.connectBus(this);
    m_Timer.connectTimer(this);
    m_Screen.connectScreen(this);

    m_InputStatus.reg = 0xCF;

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
    if (cart.get()->c_Write(addr, data)) //Cartridge
    {
    }
    else if (addr >= 0x8000 && addr <= 0x9FFF) //VRAM
    {
        if (m_Screen.LCD_Control.LCD_Enable == 0)
        {
            uint16_t mAddr = addr & 0x1FFF;
            m_VRAM.get()[mAddr] = data;
        }
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF) //Cartridge RAM
    {
        uint16_t mAddr = addr & 0x1FFF;
        cart.get()->m_Ram[mAddr] = data;
    }
    else if ((addr >= 0xC000 && addr <= 0xDFFF) || (addr >= 0xE000 && addr <= 0xFDFF)) //WRAM
    {
        uint16_t mAddr = addr & 0x1FFF;
        a_WRAM[mAddr] = data;
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F) //OAM
    {
        if ((m_Screen.LCD_Control.LCD_Enable == 0) && (m_Screen.LCD_Status.Mode_Flag == 0 || m_Screen.LCD_Status.Mode_Flag == 1))
        {
            uint16_t mAddr = addr & 0x00FF;
            a_OAM[mAddr] = data;
        }
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F) //IO Ports
    {
        switch (addr)
        {
        case JOYPAD:
            m_InputStatus.reg = data;
            break;
        case IF:
            m_IRFlag.reg = data;
            break;
        case LCDC:
            m_Screen.lcd_Write(data, addr);
            break;
        case LCDS:
            m_Screen.lcd_Write(data, addr);
            break;
        case SCY:
            m_Screen.m_SCY = data;
            break;
        case SCX:
            m_Screen.m_SCX = data;
            break;
        case LY:
            // m_Screen.m_ScanlineCount = data;
            break;
        case LYC:
            m_Screen.m_LYC = data;
            break;
        case DMA:
            m_Cpu.DoDmaTransfer(addr, data);
            break;
        case BGP:
            m_Screen.m_BGP.reg = data;
            break;
        case OBP0:
            m_Screen.m_OBP0.reg = data;
            break;
        case OBP1:
            m_Screen.m_OBP1.reg = data;
            break;
        case WY:
            m_Screen.m_WY = data;
            break;
        case WX:
            m_Screen.m_WX = data;
            break;
        default:
            break;
        }
    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE) //HRAM
    {
        uint16_t mAddr = (addr & 0x00FF);
        a_HRAM[mAddr] = data;
    }
    else if (addr == 0xFFFF) //Interrupts
    {
        m_IEFlag.reg = data;
    }
}

uint8_t Bus::read(uint16_t addr)
{
    uint8_t data;

    if (cart.get()->c_Read(addr, data))
    {
    }
    else if (addr >= 0x8000 && addr <= 0x9FFF) //VRAM
    {
        if (m_Screen.LCD_Control.LCD_Enable == 0)
        {
            uint16_t mAddr = addr & 0x1FFF;
            data = m_VRAM.get()[mAddr];
        }
    }
    else if (addr >= 0xA000 && addr <= 0xBFFF) //Cartridge RAM
    {
        uint16_t mAddr = addr & 0x1FFF;
        data = cart.get()->m_Ram[mAddr];
    }
    else if ((addr >= 0xC000 && addr <= 0xDFFF) || (addr >= 0xE000 && addr <= 0xFDFF)) //WRAM
    {
        uint16_t mAddr = addr & 0x1FFF;
        data = a_WRAM[mAddr];
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F) //OAM
    {
        if ((m_Screen.LCD_Control.LCD_Enable == 0) && (m_Screen.LCD_Status.Mode_Flag == 0 || m_Screen.LCD_Status.Mode_Flag == 1))
        {
            uint16_t mAddr = addr & 0x00FF;
            data = a_OAM[mAddr];
        }
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F) //IO Ports
    {
        switch (addr)
        {
        case JOYPAD:
            data = m_InputStatus.reg;
            break;
        case IF:
            data = m_IRFlag.reg;
            break;
        case LCDC:
            data = m_Screen.lcd_Read(addr);
            break;
        case LCDS:
            data = m_Screen.lcd_Read(addr);
            break;
        case SCY:
            data = m_Screen.m_SCY;
            break;
        case SCX:
            data = m_Screen.m_SCX;
            break;
        case LY:
            data = m_Screen.m_ScanlineCount;
            break;
        case LYC:
            data = m_Screen.m_LYC;
            break;
        case DMA:
            data = 0xFF;
            break;
         case BGP:
            data = m_Screen.m_BGP.reg;           
            break;
        case OBP0:
            data = m_Screen.m_OBP0.reg;
            break;
        case OBP1:
            data = m_Screen.m_OBP1.reg;
            break;
        case WY:
            data = m_Screen.m_WY;
            break;
        case WX:
            data = m_Screen.m_WX;
            break;

        default:
            break;
        }
    }

    else if (addr >= 0xFF80 && addr <= 0xFFFE) //HRAM
    {
        uint16_t mAddr = (addr & 0x00FF);
        data = a_HRAM[mAddr];
    }
    else if (addr == 0xFFFF) //Interrupt register
    {
        data = m_IEFlag.reg;
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
    m_Screen.GraphicsTick();
    m_Timer.DivTick();
    m_Timer.TimaTick();
}
void Bus::BusReset()
{
    m_Cpu.ResetCpu();
}
