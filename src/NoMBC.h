#include "MBC.h"

class NoMBC : public MBC_Base
{
    public:
        NoMBC();
        ~NoMBC();

        bool mbcRead(uint16_t addr, uint32_t &mbcAddr) override;
        bool mbcWrite(uint16_t addr, uint8_t data, uint16_t &mbcAddr) override;
        void Set(uint8_t data) override;
    
};
