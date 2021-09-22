#pragma once

#include "cartridge.h"
#include "Z80g.h"
#include <array>
#include <memory>

class Bus
{
    public:

        Bus();
        ~Bus();
        
        Z80g cpu;
        std::shared_ptr<Cartridge> cart;
        
        std::array<uint8_t, 64 * 1024> AddressBus;        


        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr);

        void InsertGame(std::shared_ptr<Cartridge> &Cartridge);
        void BusClock();
        void Reset();

};


