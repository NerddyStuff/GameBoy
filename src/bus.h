#pragma once

#define OAM 0xFE00

#define JOYPAD 0xFF00
#define DIV 0xFF04
#define TIMA 0xFF05
#define TMA 0xFF06
#define TAC 0xFF07
#define IF 0xFF0F
#define LCDC 0xFF40
#define LCDS 0xFF41
#define SCY 0xFF42
#define SCX 0xFF43
#define LY 0xFF44
#define LYC 0xFF45
#define DMA 0xFF46
#define BGP 0xFF47
#define OBP0 0xFF48
#define OBP1 0xFF49
#define WY 0xFF4A
#define WX 0xFF4B
#define IE 0xFFFF

#define VRAMSIZE 0x1FFF

#include <iostream>
#include <memory>

#include "PPU.h"
#include "Z8080.h"
#include "cartridge.h"
#include "Timer.h"


class Bus
{
public:
    Bus();
    ~Bus();

    std::shared_ptr<Cartridge> cart; //
    Z8080 m_Cpu;                     //  Devices on the Bus
    Timer m_Timer;                   //
    PPU m_PPU;                       //

    std::unique_ptr<uint8_t[]> a_WRAM = std::make_unique<uint8_t[]>(static_cast<size_t>(1024 * 8));
    std::unique_ptr<uint8_t[]> a_OAM  = std::make_unique<uint8_t[]>(static_cast<size_t>(0xA0));
    std::unique_ptr<uint8_t[]> a_HRAM = std::make_unique<uint8_t[]>(static_cast<size_t>(0x7E + 1));
    std::unique_ptr<uint8_t[]> m_VRAM = std::make_unique<uint8_t[]>(static_cast<size_t>(VRAMSIZE + 1));

    bool m_IMEFlag = true;

    union
    {
        struct
        {
            uint8_t u_Input_Right_A : 1;    // Bit 0
            uint8_t u_Input_Left_B : 1;     // Bit 1
            uint8_t u_Input_Up_Select : 1;  // Bit 2
            uint8_t u_Input_Down_Start : 1; // Bit 3
            uint8_t u_DirectionSelect : 1;  // Bit 4
            uint8_t u_ActionSelect : 1;     // Bit 5
            uint8_t unused : 2;             // Bits 6 - 7
        };

        uint8_t reg;

    } m_InputStatus;

    union
    {
        struct
        {
            uint8_t u_VBlank_interrupt : 1;
            uint8_t u_LCDStat_Interrupt : 1;
            uint8_t u_Timer_Interrupt : 1;
            uint8_t u_Serial_Interrupt : 1;
            uint8_t u_JoyPad_Interrupt : 1;
            uint8_t unused : 3;
        };
        uint8_t reg;

    } m_IEFlag; // 0xFFFF

    union
    {
        struct
        {
            uint8_t u_VBlank_interrupt : 1;
            uint8_t u_LCDStat_Interrupt : 1;
            uint8_t u_Timer_Interrupt : 1;
            uint8_t u_Serial_Interrupt : 1;
            uint8_t u_JoyPad_Interrupt : 1;
            uint8_t unused : 3;
        };
        uint8_t reg;

    } m_IRFlag; // 0xFF0F

    uint8_t m_SerialData;   
    uint8_t m_STC;          // Serial Transfer Control

    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr);

    void InsertGame(std::shared_ptr<Cartridge> &Cartridge);
    void BusClock();
    void BusReset();

    // SDL related functions
    void UpdateKeys(bool &quit);
};
