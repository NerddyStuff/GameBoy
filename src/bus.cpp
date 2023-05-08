#include "bus.h"

Bus::Bus()
{
    std::cout << "Gameboy created\n";
    m_Cpu.connectBus(this);
    m_Timer.connectTimer(this);
    m_PPU.connectScreen(this);

    m_InputStatus.reg = 0xCF;
};

Bus::~Bus(){

};

void Bus::write(uint16_t addr, uint8_t data)
{
    if (cart.get()->c_Write(addr, data)) // Cartridge
    {
    }
    else if (addr >= 0x8000 && addr <= 0x9FFF) // VRAM
    {
        if (m_PPU.LCD_Status.Mode_Flag != 3)
        {
            uint16_t mAddr = (addr & 0x1FFF);
            m_VRAM.get()[mAddr] = data;
        }
    }
    else if ((addr >= 0xA000 && addr <= 0xBFFF) && cart->ramEnable) // Cartridge RAM
    {
        uint16_t mAddr = addr & 0x1FFF;
        cart.get()->m_Ram[mAddr] = data;
    }
    else if ((addr >= 0xC000 && addr <= 0xDFFF) || (addr >= 0xE000 && addr <= 0xFDFF)) // WRAM
    {
        uint16_t mAddr = addr & 0x1FFF;
        a_WRAM.get()[mAddr] = data;
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F) // OAM
    {
        if ((m_PPU.LCD_Control.LCD_Enable == 0) && (m_PPU.LCD_Status.Mode_Flag == 0 || m_PPU.LCD_Status.Mode_Flag == 1))
        {
            uint16_t mAddr = (addr & 0x00FF);
            a_OAM.get()[mAddr] = data;
        }
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F) // IO Ports
    {
        switch (addr)
        {
        case JOYPAD:
            m_InputStatus.reg = data;
            break;
        case 0xFF01:
            m_SerialData = data;
            break;
        case 0xFF02:
            m_STC = data;
            break;
        case DIV:
            m_Timer.t_Write(addr, data);
            break;
        case TIMA:
            m_Timer.t_Write(addr, data);
            break;
        case TMA:
            m_Timer.t_Write(addr, data);
            break;
        case TAC:
            m_Timer.t_Write(addr, data);
            break;
        case IF:
            m_IRFlag.reg = data;
            break;
        case LCDC:
            m_PPU.PPU_Write(data, addr);
            break;
        case LCDS:
            m_PPU.PPU_Write(data, addr);
            break;
        case SCY:
            m_PPU.m_SCY = data;
            break;
        case SCX:
            m_PPU.m_SCX = data;
            break;
        case LY:
            m_PPU.m_ScanlineCount = 0;
            break;
        case LYC:
            m_PPU.m_LYC = data;
            break;
        case DMA:
            m_Cpu.DoDmaTransfer(addr, data);
            break;
        case BGP:
            m_PPU.m_BGP.reg = data;
            break;
        case OBP0:
            m_PPU.m_OBP0.reg = data;
            break;
        case OBP1:
            m_PPU.m_OBP1.reg = data;
            break;
        case WY:
            m_PPU.m_WY = data;
            break;
        case WX:
            m_PPU.m_WX = data;
            break;
        default:
            break;
        }
    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE) // HRAM
    {
        uint16_t mAddr = (addr & 0x00FF);
        a_HRAM.get()[mAddr] = data;
    }
    else if (addr == 0xFFFF) // Interrupts
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
    else if (addr >= 0x8000 && addr <= 0x9FFF) // VRAM
    {
        if (m_PPU.LCD_Status.Mode_Flag != 3)
        {
            uint16_t mAddr = (addr & 0x1FFF);
            data = m_VRAM.get()[mAddr];
        }
    }
    else if ((addr >= 0xA000 && addr <= 0xBFFF) && cart->ramEnable) // Cartridge RAM
    {
        uint16_t mAddr = (addr & 0x1FFF);
        data = cart->m_Ram[mAddr];
    }
    else if ((addr >= 0xC000 && addr <= 0xDFFF) || (addr >= 0xE000 && addr <= 0xFDFF)) // WRAM
    {
        uint16_t mAddr = (addr & 0x1FFF);
        data = a_WRAM.get()[mAddr];
    }
    else if (addr >= 0xFE00 && addr <= 0xFE9F) // OAM
    {
        if ((m_PPU.LCD_Control.LCD_Enable == 0) && (m_PPU.LCD_Status.Mode_Flag == 0 || m_PPU.LCD_Status.Mode_Flag == 1))
        {
            uint16_t mAddr = (addr & 0x00FF);
            data = a_OAM.get()[mAddr];
        }
    }
    else if (addr >= 0xFF00 && addr <= 0xFF7F) // IO Ports
    {
        switch (addr)
        {
        case JOYPAD:
            data = m_InputStatus.reg;
            break;
        case 0xFF01:
            data = m_SerialData;
            break;
        case 0xFF02:
            data = m_STC;
            break;
        case DIV:
            data = m_Timer.t_Read(addr);
            break;
        case TIMA:
            data = m_Timer.t_Read(addr);
            break;
        case TMA:
            data = m_Timer.t_Read(addr);
            break;
        case TAC:
            data = m_Timer.t_Read(addr);
            break;
        case IF:
            data = m_IRFlag.reg;
            break;
        case LCDC:
            data = m_PPU.PPU_Read(addr);
            break;
        case LCDS:
            data = m_PPU.PPU_Read(addr);
            break;
        case SCY:
            data = m_PPU.m_SCY;
            break;
        case SCX:
            data = m_PPU.m_SCX;
            break;
        case LY:
            data = m_PPU.m_ScanlineCount;
            break;
        case LYC:
            data = m_PPU.m_LYC;
            break;
        case DMA:
            data = 0xFF;
            break;
        case BGP:
            data = m_PPU.m_BGP.reg;
            break;
        case OBP0:
            data = m_PPU.m_OBP0.reg;
            break;
        case OBP1:
            data = m_PPU.m_OBP1.reg;
            break;
        case WY:
            data = m_PPU.m_WY;
            break;
        case WX:
            data = m_PPU.m_WX;
            break;

        default:
            break;
        }
    }
    else if (addr >= 0xFF80 && addr <= 0xFFFE) // HRAM
    {
        uint16_t mAddr = (addr & 0x00FF);
        data = a_HRAM.get()[mAddr];
    }
    else if (addr == 0xFFFF) // Interrupt register
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
    // m_PPU.GraphicsTick();
    m_Timer.DivTick();
    m_Timer.TimaTick();

    uint8_t s = read(0xFF02);

    if (s == 0x81)
    {
        uint8_t c = m_SerialData;
        printf("%c", c);
        write(0xFF02, 0x00);
    }
    
}
void Bus::BusReset()
{
    m_Cpu.ResetCpu();
}
void Bus::UpdateKeys(bool &quit)
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = false;
                break;

            default:
                break;
            }
            break;
        case SDL_QUIT:
            quit = false;
        default:
            break;
        }
    }
}