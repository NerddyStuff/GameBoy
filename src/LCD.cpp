#include "LCD.h"
#include "bus.h"

LCD::LCD()
{
    for (uint32_t i = 0; i < 0x5A00; i++)
    {
        FrameBuffer.get()[i] = 0x00;
    }
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

    if (m_ScanlineCycles <= 80) // Mode 2 OAM SEARCH
    {
        LCD_Status.Mode_Flag = 2;
        StatInterEnabled = (LCD_Status.Mode_2_Interrupt == 1 ? true : false);
    }
    if (m_ScanlineCycles >= 81 && m_ScanlineCycles <= 252) // Mode 3 LCDC WRITE
    {
        LCD_Status.Mode_Flag = 3;
    }
    if (m_ScanlineCycles >= 253 && m_ScanlineCycles <= 456) // Mode 0 HBLANK
    {
        LCD_Status.Mode_Flag = 0;
        StatInterEnabled = (LCD_Status.Mode_0_Interrupt == 1 ? true : false);
    }
    if (m_ScanlineCount == 144) // Mode 1 VBLANK
    {
        LCD_Status.Mode_Flag = 1;
        StatInterEnabled = (LCD_Status.Mode_1_Interrupt == 1 ? true : false);
    }

    if (StatInterEnabled && (CurrentMode != LCD_Status.Mode_Flag))
    {
        ptr->write(IF, 0x02); // Interrupt request
    }

    if (LCD_Status.LYC_LY_Flag == 1 && LCD_Status.LYC_LY_Interrupt == 1)
    {
        ptr->write(IF, 0x02); // Interrupt request
    }
}
void LCD::DrawScanline()
{
    if (LCD_Control.BG_Window_Priority == 1)
        DrawBKG();

    if (LCD_Control.OBJ_Enable == 1)
        DrawOBJ();
}
void LCD::GraphicsTick()
{
    m_ScanlineCycles++;

    SetLCDStat();

    if (m_ScanlineCycles == 456)
    {
        m_ScanlineCycles = 0;
        m_ScanlineCount++;

        if (m_ScanlineCount == 144)
        {
            ptr->write(IF, 0x01);
        }
    }

    if (m_ScanlineCount >= 153)
        m_ScanlineCount = 0;

    if (m_ScanlineCount <= 144)
        DrawScanline();
}

void LCD::DrawBKG()
{
    bool UsingSignedAddr;

    uint8_t WindowX = m_WX - 7;
    uint8_t fetcherX;
    uint8_t fetcherY;
    uint16_t TileMap;
    uint16_t TileAddr;

    // Chooses what tile map to use
    switch (LCD_Control.Window_Enable)
    {
    case 0:
        TileMap = LCD_Control.BG_Tile_Map_Area == 1 ? 0x9C00 : 0x9800;
        break;
    case 1:
        TileMap = LCD_Control.Window_TileMap_Area == 1 ? 0x9C00 : 0x9800;
        break;
    default:
        TileMap = LCD_Control.BG_Tile_Map_Area == 1 ? 0x9C00 : 0x9800;
        printf("Used default tile map, LCDC Bit 5");
        break;
    }

    // This chooses between the 2 addressing modes for tiles
    switch (LCD_Control.BG_and_Window_Tile_Data)
    {
    case 0:
        TileAddr = 0x8800;
        UsingSignedAddr = true;
        break;
    case 1:
        TileAddr = 0x8000;
        UsingSignedAddr = false;
        break;
    default:
        TileAddr = 0x8000;
        UsingSignedAddr = false;
        printf("Default addressing mode used, LCDC Bit 4");
        break;
    }

    // If the current tile is a window tile, set fetcherX = m_WX, if not, calculate the x coordinate using this formula
    // fetcherX can be 0 - 31
    // (m_SCX >= WindowX) ? fetcherX = WindowX : ((m_SCX / 8) & 0x1F);

    // If the current tile is a window tile, set fetcherY = m_WY, if not, calculate the y coordinate using this formula
    // fetcherY can be 0 - 159
    // (m_SCY >= m_WY) ? fetcherY = m_WY : ((m_ScanlineCount + m_SCY) & 255);

    // Get the Ypos of the tile depending if the window is active or not
    if (LCD_Control.Window_Enable == 1)
        fetcherY = m_ScanlineCount - m_WY;
    else
        fetcherY = m_SCY + m_ScanlineCount;

    uint16_t tileY = ((reinterpret_cast<uint8_t>(fetcherY) / 8) * 32); // Get the Ypos of the tile to start drawing

    for (size_t tile = 0; tile < 20; tile++)
    {
        fetcherX = ((tile * 8) + m_SCX);
        uint16_t tileX = (fetcherX / 8);

        uint16_t tile_Addr = TileMap + tileX + tileY; // Tile identifier

        // Get the tile id
        int16_t tile_id;
        UsingSignedAddr == true ? tile_id = reinterpret_cast<uint8_t>(ptr->read(tile_Addr)) : tile_id = (int8_t)(ptr->read(tile_Addr));

        // Get tile location
        uint16_t tile_loc;
        UsingSignedAddr == true ? tile_loc += (tile_id * 16) : tile_loc += ((tile_id + 128) * 16);

        // What line of the tile are we on?
        uint8_t current_line = (fetcherY % 8);
        current_line *= 2;

        uint8_t tile_lsb = ptr->read(tile_loc + current_line);
        uint8_t tile_msb = ptr->read(tile_loc + current_line + 1);

        for (size_t tilepixel = 0; tilepixel < 8; tilepixel++)
        {
            uint8_t PixelData = (tile_msb & 0x01) + (tile_lsb & 0x01);
            tile_lsb >>= 1;
            tile_msb >>= 1;

            uint32_t colorval;

            switch (PixelData)
            {
            case 0:
                colorval = 0x00FFFFFF;
                break;
            case 1:
                colorval = 0x00CCCCCC;
                break;
            case 2:
                colorval = 0x00777777;
                break;
            case 3:
                colorval = 0x00000000;
                break;
            default:
                printf("Pixel data fetch fail\n");
                colorval = 4;
                // Sets color value to 4,
                break;
            }

            if (colorval == 4)
                printf("Frame Buffer write not preformed\n");
            else
            {
                if (m_ScanlineCount > 144)
                {
                    // Do not write if the scanline is greater that 144

                    // FrameBuffer.get()[(tile * 8) + tilepixel] = colorval;
                    // FrameBuffer.get()[tile * 144] == 0 ? printf("Framebuffer has not been written too\n") : printf("Succesfull write\n");
                }
                else
                {
                    FrameBuffer.get()[((tile * 8) + tilepixel) * m_ScanlineCount] = colorval;
                    // FrameBuffer.get()[((tile * 8) + tilepixel) * m_ScanlineCount] == 0 ? printf("Framebuffer has not been written too\n") : printf("Succesfull write\n");
                }
            }
        }
    }
}

void LCD::DrawOBJ()
{
}