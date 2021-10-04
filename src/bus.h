#pragma once

#define JOYPAD 0xFF00
#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07

#define IF 0xFF0F
#define IE 0xFFFF

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
        
        Timer m_Timer;                      //
        Z80g m_Cpu;                         //  Devices on the Bus
        std::shared_ptr<Cartridge> cart;    //
        
        std::array<uint8_t, 1024 * 4> a_WRAM;                                         //
        std::array<uint8_t, 1024 * 8> a_VRAM;                                         //  Memory devices on the bus
        std::array<uint8_t, 0xA0> a_OAM;                                              //
        std::array<uint8_t, 0x7F + 1>  a_IOPorts;                                     //
        std::unique_ptr<uint8_t[]> a_HRAM = std::make_unique<uint8_t[]>(0x7E + 1);    //

        uint8_t m_InputStatus;
        
        bool m_IMEFlag = false;
        uint8_t m_IEFlag{0x00};

        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr);

        void InsertGame(std::shared_ptr<Cartridge> &Cartridge);
        void BusClock();
        void BusReset();

};


