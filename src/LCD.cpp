#include "LCD.h"

#define VRAMSIZE 0x1FFF

LCD::LCD()
{
    m_VRAM = std::make_unique<uint8_t[]>(static_cast<size_t>(VRAMSIZE));
}

LCD::~LCD()
{
    
}