#pragma once

#include <cstdint>

#define CPUSPEED 4194304

class Bus;

class Timer
{
private:

    Bus *busp = nullptr;
    uint8_t DivCycles = 0;
    bool TimerCheck();
    
    uint8_t m_DivRegister;
    uint8_t m_TacRegister;
    uint32_t m_TimaRegister;
    uint8_t m_TmaRegister;

    uint8_t m_Speed;
    uint32_t m_RequiredCycles;
    uint32_t m_CurrentCycles = 0;

public:
    
    Timer();
    ~Timer();

    void TimaTick();
    void DivTick();
    uint8_t t_Read(uint16_t addr);
    void t_Write(uint16_t addr, uint8_t data);

    void connectTimer(Bus *ptr) { busp = ptr; }
};
