#include "LCD.h"
#include "bus.h"

LCD::LCD()
{
}

LCD::~LCD()
{
}

uint8_t LCD::lcd_Read(uint16_t addr)
{
    if (addr == LCDC)
    {
        return LCD_Control.reg;
    }
    if (addr == LCDS)
    {
        return LCD_Status.reg;
    }
    if (addr == LY)
    {
        return m_ScanlineCount;
    }

    else
    {
        return 0xFF;
    }
}
void LCD::lcd_Write(uint8_t data, uint16_t addr)
{
    if (addr == LCDC)
    {
        LCD_Control.reg = data;
    }
    else if (addr == LCDS)
    {
        LCD_Status.reg = data;
    }
}
void LCD::SetLCDStat()
{

    uint8_t CurrentMode = LCD_Status.Mode_Flag;
    bool StatInterEnabled;

    if (LCD_Control.LCD_Enable == 0)
    {
        LCD_Status.Mode_Flag = 1;
        m_ScanlineCount = 0;
        m_ScanlineCycles = 0;
    }

    m_ScanlineCount == m_LYC ? LCD_Status.LYC_LY_Flag = 1 : LCD_Status.LYC_LY_Flag = 0; // If LYC and ly are equal, set the apropriate bit, if not set it off

    if (m_ScanlineCycles <= 80)     // Mode 2
    {
        LCD_Status.Mode_Flag = 2;
        StatInterEnabled = (LCD_Status.Mode_2_Interrupt == 1 ? true : false);

    }
    if (m_ScanlineCycles >= 81 && m_ScanlineCycles <= 252)      // Mode 3
    {
        LCD_Status.Mode_Flag = 3;
    }
    if (m_ScanlineCycles >= 253 && m_ScanlineCycles <= 456)     // Mode 0
    {
        LCD_Status.Mode_Flag = 0;
        StatInterEnabled = (LCD_Status.Mode_0_Interrupt == 1 ? true : false);
    }
    if (m_ScanlineCount == 144)                                 // Mode 1
    {
        LCD_Status.Mode_Flag = 1;
        StatInterEnabled = (LCD_Status.Mode_1_Interrupt == 1 ? true : false);
    }

    if (StatInterEnabled && (CurrentMode != LCD_Status.Mode_Flag))
    {
        ptr->write(IF, 0x02);
    }
    
    if (LCD_Status.LYC_LY_Flag == 1 && LCD_Status.LYC_LY_Interrupt == 1)
    {
        ptr->write(IF, 0x02);
    }
}
void LCD::GraphicsTick()
{
    m_ScanlineCycles++;

    SetLCDStat();

    if (m_ScanlineCycles == 456)
    {
        m_ScanlineCycles = 0;
        m_ScanlineCount++;

        if (m_ScanlineCount >= 144)
        {
            ptr->write(IF, 0x01);
        }
    }
}