#pragma once

#include "cartridge.h"
#include "gameboy.h"
#include <array>

class Bus
{

    public:

        Bus();
        ~Bus();
        
    public:

        Z80g cpu;
        Cartridge game;
        
        std::array<uint8_t, 64 * 1024> AddressBus;        


        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr);


};


