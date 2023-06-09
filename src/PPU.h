#pragma once

#include <SDL2/SDL.h>
#include <memory>
#include <array>

class Bus;
class PPU
{
private:
    Bus *ptr = nullptr;

public:
    PPU();
    ~PPU();

    SDL_Window *window;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    uint8_t m_PixelValues[256 * 256 * 4];
    std::unique_ptr<uint8_t[]> m_FrameBufferA = std::make_unique<uint8_t[]>(static_cast<size_t>(160 * 144 * 4));

    uint8_t m_LYC{0};        // LYC Compare
    uint8_t m_ScanlineCount; // LY
    uint8_t m_SCY;           // Scroll Y
    uint8_t m_SCX;           // Scroll X
    uint8_t m_WY;            // Window y position
    uint8_t m_WX;            // Window x position -7
    uint16_t m_ScanlineCycles = 0;

    union
    {
        struct
        {
            uint8_t BG_Window_Priority : 1;      // Bit 0
            uint8_t OBJ_Enable : 1;              // Bit 1
            uint8_t OBJ_Size : 1;                // Bit 2
            uint8_t BG_Tile_Map_Area : 1;        // Bit 3
            uint8_t BG_and_Window_Tile_Data : 1; // Bit 4
            uint8_t Window_Enable : 1;           // Bit 5
            uint8_t Window_TileMap_Area : 1;     // Bit 6
            uint8_t LCD_Enable : 1;              // Bit 7
        };

        uint8_t reg;

    } LCD_Control;
    union
    {
        struct
        {
            uint8_t Mode_Flag : 2;        // Bits 0 - 1
            uint8_t LYC_LY_Flag : 1;      // Bit 2
            uint8_t Mode_0_Interrupt : 1; // Bit 3
            uint8_t Mode_1_Interrupt : 1; // Bit 4
            uint8_t Mode_2_Interrupt : 1; // Bit 5
            uint8_t LYC_LY_Interrupt : 1; // Bit 6
            uint8_t unused : 1;           // Bit 7 (Not used)
        };

        uint8_t reg;

    } LCD_Status;

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

    } m_BGP; // Background palette data
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

    } m_OBP0; // Object palette data 0
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

    } m_OBP1; // Object palette data 1

    void GraphicsTick();
    void SetLCDStat();

    bool DrawScanline();
    void DrawBKG();
    void DrawOBJ();

    uint8_t GetColor(uint8_t array[], uint8_t x);    

    uint8_t PPU_Read(uint16_t addr);
    void PPU_Write(uint8_t data, uint16_t addr);
    void connectScreen(Bus *p) { ptr = p; }

    // Functions using SDL
    void UpdateScreen(const void *pixeldata, int size);
};
