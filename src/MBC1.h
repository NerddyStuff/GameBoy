#include "MBC.h"

class MBC_1 : public MBC_Base
{

public:
    MBC_1();
    ~MBC_1();

    uint8_t RomSize;
    uint8_t BankCount;

    uint8_t m_RamEnableRegister; // 0x0000 - 0x1FFF

    union
    {
        struct
        {
            uint8_t bit_0 : 1;
            uint8_t bit_1 : 1;
            uint8_t bit_2 : 1;
            uint8_t bit_3 : 1;
            uint8_t bit_4 : 1;
            uint8_t bit_5 : 1;
            uint8_t unused : 2;
        };

        uint8_t reg;

    } m_ROMBankNumberRegister{0x01}; // 0x2000 - 0x3FFF

    union
    {
        struct
        {
            uint8_t bit_0 : 1;
            uint8_t bit_1 : 1;
            uint8_t unused : 5;
        };

        uint8_t reg;
    } m_RAMBankRegister; // 0x4000 - 0x5FFF

    bool m_BankingMode; // 0x6000 - 0x7FFF

    bool mbcRead(uint16_t addr, uint32_t &mbcaddr) override;
    bool mbcWrite(uint16_t addr, uint8_t data, uint16_t &mbcAddr) override;
    void Set(uint8_t data) override;
};
