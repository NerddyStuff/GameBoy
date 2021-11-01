#pragma once

#include <memory>

class Bus;
class LCD
{
private:
    Bus *ptr = nullptr;

public:
    LCD();
    ~LCD();

    union
    {
        struct
        {
            uint8_t BG_Window_Priority : 1;
            uint8_t OBJ_Enable : 1;
            uint8_t OBJ_Size : 1;
            uint8_t BG_Tile_Map_Area : 1;
            uint8_t BG_and_Window_Tile_Data : 1;
            uint8_t Window_Enable : 1;
            uint8_t Window_TileMap_Area : 1;
            uint8_t LCD_Enable : 1;
        };

        uint8_t reg;

    } LCD_Control;
    union
    {
        struct
        {
            uint8_t Mode_Flag : 2;
            uint8_t LYC_LY_Flag : 1;
            uint8_t Mode_0_Interrupt : 1;
            uint8_t Mode_1_Interrupt : 1;
            uint8_t Mode_2_Interrupt : 1;
            uint8_t LYC_LY_Interrupt : 1;
            uint8_t unused : 1;
        };

        uint8_t reg;

    } LCD_Status;

    uint8_t m_LYC{0};
    uint8_t m_ScanlineCount; //LY
    uint8_t m_SCY;
    uint8_t m_SCX;
    uint8_t m_WY; 
    uint8_t m_WX;

    union 
    {
        struct 
        {
            uint8_t u_Index0 : 2;
            uint8_t u_Index1 : 2;
            uint8_t u_Index2 : 2;
            uint8_t u_Index3 : 2;
            
        };

        uint8_t reg;
        
    } m_BGP;
    union 
    {
        struct 
        {
            uint8_t u_Index0 : 2;
            uint8_t u_Index1 : 2;
            uint8_t u_Index2 : 2;
            uint8_t unused : 2;
            
        };

        uint8_t reg;
        
    } m_OBP0;
    union 
    {
        struct 
        {
            uint8_t u_Index0 : 2;
            uint8_t u_Index1 : 2;
            uint8_t u_Index2 : 2;
            uint8_t unused : 2;
            
        };

        uint8_t reg;
        
    } m_OBP1;

    uint16_t m_ScanlineCycles = 0;

    void GraphicsTick();
    void SetLCDStat();

    uint8_t lcd_Read(uint16_t addr);
    void lcd_Write(uint8_t data, uint16_t addr);

    void connectScreen(Bus *p) { ptr = p; }
};
