#pragma once
#include <cstdint>

#define ROMONLY 0x00
#define MBC1 0x01
#define MBC1_RAM 0x02
#define MBC1_RAM_BATTERY 0x03
#define MBC2 0x05
#define MBC2_BATTERY 0x06
// #define ROM_RAM 0x08
// #define ROM_RAM_BATTERY 0x09
#define MMM01 0x0B
#define MMM01_RAM 0x0C
#define MMM01_RAM_BATTERY 0x0D
#define MBC3_TIMER_BATTERY 0x0F
#define MBC3_TIMER_RAM_BATTERY 0x10
#define MBC3 0x11
#define MBC3_RAM 0x12
#define MBC3_RAM_BATTERY 0x13
#define MBC5 0x19
#define MBC5_RAM 0x1A
#define MBC5_RAM_BATTERY 0x1B
#define MBC5_RUMBLE 0x1C
#define MBC5_RUMBLE_RAM 0x1D
#define MBC5_RUMBLE_RAM_BATTERY 0x1E
#define MBC6 0x20
#define MBC7_SENSOR_RUMBLE_RAM_BATTERY 0x22
#define POCKET_CAMERA 0xFC
#define BANDAI_TAMA5 0xFD
#define HuC3 0xFE
#define HuC1_RAM_BATTERY 0xFF

// Defines rom size
#define	KByte_32 0x00
#define	KByte_64 0x01
#define	KByte_128 0x02
#define	KByte_256 0x03	
#define	KByte_512 0x04	
#define	MByte_1 0x05
#define	MByte_2 0x06
#define	MByte_4 0x07
#define	MByte_8 0x08

class MBC_Base
{
    public:
        MBC_Base();
        ~MBC_Base();

        virtual bool mbcRead(uint16_t addr, uint32_t &mbcaddr) = 0;
        virtual bool mbcWrite(uint16_t addr, uint32_t &mbcAddr) = 0;

};




