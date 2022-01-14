#include "NoMBC.h"

NoMBC::NoMBC()
{

}
NoMBC::~NoMBC()
{
    
}

bool NoMBC::mbcRead(uint16_t addr, uint16_t &mbcAddr)
{
    if (addr >= 0x0000 && addr <= 0x7FFF)
    {
        mbcAddr = addr;
        return true;
    }
    
    return false;
}

bool NoMBC::mbcWrite(uint16_t addr, uint16_t &mbcAddr)
{
    if (addr >= 0x0000 && addr <= 0x7FFF)
    {
        mbcAddr = addr;
        return true;
    }
    
    return false;
}