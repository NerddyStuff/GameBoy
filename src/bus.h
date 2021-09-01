#pragma once

#include "gameboy.h"

class Bus
{

public:
    
    Z80g cpu;
    uint8_t Addresses[0xFFFFu];
    
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
    
    
    Bus();
    ~Bus();
};


