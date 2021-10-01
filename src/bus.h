#pragma once

#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07

#include "cartridge.h"
#include "Z80g.h"
#include "Timer.h"

#include <array>
#include <memory>

class Bus
{
    public:

        Bus();
        ~Bus();
        
        Timer m_Timer;
        Z80g m_Cpu;
        std::shared_ptr<Cartridge> cart;
        
        std::array<uint8_t, 1024 * 4> WRAM;
        std::array<uint8_t, 1024 * 8> VRAM;
        std::array<uint8_t, 0xA0> OAM;        


        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr);

        void InsertGame(std::shared_ptr<Cartridge> &Cartridge);
        void BusClock();
        void BusReset();

};


