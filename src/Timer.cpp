#include "Timer.h"
#include "bus.h"

Timer::Timer()
{

}
Timer::~Timer()
{
    
}
bool Timer::TimerCheck()
{
    return ((m_TacRegister & 0x04) == 1) ? true : false;
}
void Timer::DivTick()
{
    DivCycles += 1;

    if (DivCycles >= 255)
    {
        DivCycles = 0;
        m_DivRegister += 1;
    }
}
void Timer::TimaTick()
{
    uint8_t SpeedCheck = (m_TacRegister & 0x0F);

    if (TimerCheck())
    {
        if (m_Speed != SpeedCheck)
        {
            m_Speed = (m_TacRegister & 0x0F);
            switch (m_Speed)
            {
            case 0x00:
                m_RequiredCycles = 1024;
                break;
            case 0x01:
                m_RequiredCycles = 16;
                break;
            case 0x02:
                m_RequiredCycles = 64;
                break;
            case 0x03:
                m_RequiredCycles = 256;
                break;
            default:
                m_RequiredCycles = 1024;
                break;
            }
        }

        m_CurrentCycles += 1;
        if (m_CurrentCycles >= m_RequiredCycles)
        {
            m_TimaRegister++;
            if (m_TimaRegister >= 255)
            {
                m_TimaRegister = m_TmaRegister;
                // Request interrupt
            }
        }
    }
}
uint8_t Timer::t_Read(uint16_t addr)
{
    switch (addr)
    {
    case DIV:
        return m_DivRegister;
        break;
    case TIMA:
        return m_TimaRegister;
        break;
    case TMA:
        return m_TmaRegister;
        break;
    case TAC:
        return m_TacRegister;
        break;
    default:
        return 0x00;
        break;
    }
}
void Timer::t_Write(uint16_t addr, uint8_t data)
{
    switch (addr)
    {
    case DIV:
        m_DivRegister = 0;
        break;
    case TIMA:
        m_TimaRegister = data;
        break;
    case TMA:
        m_TmaRegister = data;
        break;
    case TAC:
        m_TacRegister = data;
        break;
    default:

        break;
    }
}