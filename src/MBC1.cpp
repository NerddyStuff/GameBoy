#include "MBC1.h"

MBC_1::MBC_1()
{
}
MBC_1::~MBC_1()
{
}
bool MBC_1::mbcRead(uint16_t addr, uint32_t &mbcaddr)
{
    if (addr >= 0x0000 && addr <= 0x3FFF)
    {
        if (m_BankingMode)
        {
            switch (m_RAMBankRegister.reg)
            {
            case 0:
                /* code */
                break;
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
            }
        }

        mbcaddr = addr;
    }
    else if (addr >= 0x4000 && addr <= 0x7FFF)
    {
        uint8_t CurrentBank = m_ROMBankNumberRegister.reg;
        switch (BankCount)
        {
        case 4:
            CurrentBank &= 0x03;
            break;
        case 8:
            CurrentBank &= 0x07;
            break;
        case 16:
            CurrentBank &= 0x0F;
            break;
        case 32:
            CurrentBank &= 0x1F;
            break;
        case 64:
            CurrentBank &= 0x3F;
            break;
        default:
            break;
        }
        switch (CurrentBank)
        {
        case 0:
            // Load from bank 1 anyway
            mbcaddr = addr;
            return true;
            break;
        case 1:
            // Bank 1
            mbcaddr = addr;
            return true;
            break;
        case 2:
            // Bank 2, 0x4000 is 16KiB
            mbcaddr = (addr + 0x4000);
            return true;
            break;
        case 3:
            // Bank 3
            mbcaddr = (addr + 0x8000);
            return true;
            break;
        case 4:
            // Bank 4
            mbcaddr = (addr + 0xC000);
            return true;
            break;
        case 5:
            // Bank 5
            mbcaddr = (addr + 0x10000);
            return true;
            break;
        case 6:
            // Bank 6
            mbcaddr = (addr + 0x14000);
            return true;
            break;
        case 7:
            // Bank7
            mbcaddr = (addr + 0x18000);
            return true;
            break;
        case 8:
            // Bank 8
            mbcaddr = (addr + 0x1C000);
            return true;
            break;
        case 9:
            // Bank 9
            mbcaddr = (addr + 0x20000);
            return true;
            break;
        case 10:
            // Bank 10
            mbcaddr = (addr + 0x24000);
            return true;
            break;
        case 11:
            // Bank 11
            mbcaddr = (addr + 0x28000);
            return true;
            break;
        case 12:
            // Bank 12
            mbcaddr = (addr + 0x2C000);
            return true;
            break;
        case 13:
            mbcaddr = (addr + 0x30000);
            return true;
            break;
        case 14:
            // Bank 14
            mbcaddr = (addr + 0x34000);
            return true;
            break;
        case 15:
            // Bank 15
            mbcaddr = (addr + 0x38000);
            return true;
            break;
        case 16:
            // Bank 16
            mbcaddr = (addr + 0x3C000);
            return true;
            break;
        case 17:
            // Bank 17
            mbcaddr = (addr + 40000);
            return true;
            break;
        case 18:
            // Bank 18
            mbcaddr = (addr + 0x44000);
            return true;
            break;
        case 19:
            // Bank 19
            mbcaddr = (addr + 0x48000);
            return true;
            break;
        case 20:
            // Bank 20
            mbcaddr = (addr + 0x4C000);
            return true;
            break;
        case 21:
            // Bank 21
            mbcaddr = (addr + 0x50000);
            return true;
            break;
        case 22:
            // Bank 22
            mbcaddr = (addr + 0x54000);
            return true;
            break;
        case 23:
            // Bank 23
            mbcaddr = (addr + 0x58000);
            return true;
            break;
        case 24:
            // Bank 24
            mbcaddr = (addr + 0x5C000);
            return true;
            break;
        case 25:
            // Bank 25
            mbcaddr = (addr + 0x60000);
            return true;
            break;
        case 26:
            // Bank 26
            mbcaddr = (addr + 0x64000);
            return true;
            break;
        case 27:
            // Bank 27
            mbcaddr = (addr + 0x68000);
            return true;
            break;
        case 28:
            // Bank 28
            mbcaddr = (addr + 0x6C000);
            return true;
            break;
        case 29:
            // Bank 29
            mbcaddr = (addr + 0x70000);
            return true;
            break;
        case 30:
            // Bank 30
            mbcaddr = (addr + 0x74000);
            return true;
            break;
        case 31:
            // Bank 31
            mbcaddr = (addr + 0x78000);
            return true;
            break;
        case 32:
            // Bank 32
            mbcaddr = (addr + 0x7C000);
            return true;
            break;
        case 33:
            // Bank 33
            mbcaddr = (addr + 0x80000);
            return true;
            break;
        case 34:
            // Bank 34
            mbcaddr = (addr + 0x84000);
            return true;
            break;
        case 35:
            // Bank 35
            mbcaddr = (addr + 0x88000);
            return true;
            break;
        case 36:
            // Bank 36
            mbcaddr = (addr + 0x8C000);
            return true;
            break;
        case 37:
            // Bank 37
            mbcaddr = (addr + 0x90000);
            return true;
            break;
        case 38:
            // Bank 38
            mbcaddr = (addr + 0x94000);
            return true;
            break;
        case 39:
            // Bank 39
            mbcaddr = (addr + 0x98000);
            return true;
            break;
        case 40:
            // Bank 40
            mbcaddr = (addr + 0x9C000);
            return true;
            break;
        case 41:
            break;
        case 42:
            break;
        case 43:
            break;
        case 44:
            break;
        case 45:
            break;
        case 46:
            break;
        case 47:
            break;
        case 48:
            break;
        case 49:
            break;
        case 50:
            break;
        case 51:
            break;
        case 52:
            break;
        case 53:
            break;
        case 54:
            break;
        case 55:
            break;
        case 56:
            break;
        case 57:
            break;
        case 58:
            break;
        case 59:
            break;
        case 60:
            break;
        case 61:
            break;
        case 62:
            break;
        case 63:
            break;
        case 64:
            break;
        default:
            return false;
            break;
        }
    }
}
bool MBC_1::mbcWrite(uint16_t addr, uint8_t data, uint16_t &mbcaddr)
{
    if (addr >= 0x0000 && addr <= 0x1FFF)
    {
        m_RamEnableRegister = data;
        return true;
    }
    if (addr >= 0x2000 && addr <= 0x3FFF)
    {
        if (data == 0)
        {
            m_ROMBankNumberRegister.reg = 1;
        }
        else
        {
            m_ROMBankNumberRegister.reg = data;
        }
        return true;
    }
    if (addr >= 0x4000 && addr <= 0x5FFF)
    {
        m_RAMBankRegister.reg = data;
        return true;
    }
    if (addr >= 0x6000 && addr <= 0x7FFF)
    {
        data > 0 ? m_BankingMode = true : m_BankingMode = false;
        return true;
    }

    return false;
}
void MBC_1::Set(uint8_t data)
{
    RomSize = data;

    switch (RomSize)
    {
    case 0x01:
        BankCount = 4;
        break;
    case 0x02:
        BankCount = 8;
        break;
    case 0x03:
        BankCount = 16;
        break;
    case 0x04:
        BankCount = 32;
        break;
    case 0x05:
        BankCount = 64;
        break;
    default:
        break;
    }
}