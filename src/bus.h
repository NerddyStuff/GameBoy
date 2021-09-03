#pragma once

#include "cartridge.h"
#include "gameboy.h"

class Bus
{

public:
    
    Z80g cpu;
    Cartridge game;

    uint8_t AddressBus[0xFFFF];
    
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);
    
    
    Bus();
    ~Bus();
};


