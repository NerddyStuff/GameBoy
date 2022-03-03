#include "LCD.h"
#include "bus.h"

LCD::LCD()
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("GameBoy Test Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160 * 3, 144 * 3, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Failed to create window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Failed to create renderer");
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB4444, SDL_TEXTUREACCESS_STREAMING, 160, 144);
    if (texture == NULL)
    {
        printf("Failed to create texture");
    }

    ColorPallete[0] = 0xFFFFFFFF;
    ColorPallete[1] = 0xFFCCCCCC;
    ColorPallete[2] = 0xFF777777;
    ColorPallete[3] = 0x00000000;
}

LCD::~LCD()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
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
bool LCD::DrawScanline()
{
    bool drawhandle = false;

    if (LCD_Control.BG_Window_Priority == 1)
    {
        DrawBKG();
        drawhandle = true;
    }

    if (LCD_Control.OBJ_Enable == 1)
    {
        DrawOBJ();
        drawhandle = true;
    }

    return drawhandle;
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
    {
        DrawScanline();
    }
}

void LCD::DrawBKG()
{
    bool UsingSignedAddr;

    uint8_t WindowX = m_WX - 7;
    uint8_t xPos;
    uint8_t yPos;
    uint16_t TileMap;
    uint16_t TileAddrMode;

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
        TileAddrMode = 0x8800;
        UsingSignedAddr = true;
        break;
    case 1:
        TileAddrMode = 0x8000;
        UsingSignedAddr = false;
        break;
    default:
        TileAddrMode = 0x8000;
        UsingSignedAddr = false;
        printf("Default addressing mode used, LCDC Bit 4");
        break;
    }

    // If the current tile is a window tile, set xPos = m_WX, if not, calculate the x coordinate using this formula
    // xPos can be 0 - 31
    // (m_SCX >= WindowX) ? xPos = WindowX : ((m_SCX / 8) & 0x1F);

    // If the current tile is a window tile, set yPos = m_WY, if not, calculate the y coordinate using this formula
    // yPos can be 0 - 159
    // (m_SCY >= m_WY) ? yPos = m_WY : ((m_ScanlineCount + m_SCY) & 255);

    // Get the Ypos of the tile depending if the window is active
    if (LCD_Control.Window_Enable == 1)
        yPos = m_ScanlineCount - m_WY; // We dont add m_SCY because you can't scroll the window
    else
        yPos = m_SCY + m_ScanlineCount; // The added m_SCY adds the scrolling effect

    uint16_t tileY = ((reinterpret_cast<uint8_t>(yPos) / 8) * 32); // Get the Ypos of the tile to start drawing

    uint8_t current_pixel = 0;
    for (size_t current_tile = 0; current_tile < 20; current_tile++)
    {
        xPos = (current_pixel + m_SCX);

        // Get the xPos of the tile dependig if the window is active
        if (LCD_Control.Window_Enable == 1 && (current_pixel >= m_WX)) // Check if the window renders properly without the -7 here
        {
            xPos = (current_pixel - WindowX);
        }

        uint16_t tileX = (xPos / 8);

        uint16_t tile_idGet = TileMap + tileX + tileY; // The position of the tiles x and y are added with the tile map
                                                       // that was selected to get the proper TileID
        // Get the tile id
        uint16_t tile_id;
        if (UsingSignedAddr)
        {
            tile_id = (int8_t)ptr->read(tile_idGet);
        }
        else
        {
            tile_id = ptr->read(tile_idGet);
        }

        // Get tile location in memory
        UsingSignedAddr == true ? TileAddrMode += (tile_id * 16) : TileAddrMode += ((tile_id + 128) * 16);

        // What line of the tile are we on?
        uint8_t current_line = (yPos % 8);
        current_line *= 2;

        uint8_t tile_lsb = ptr->read(TileAddrMode + current_line);
        uint8_t tile_msb = ptr->read(TileAddrMode + current_line + 1);

        for (size_t tilepixel = 0; tilepixel < 8; tilepixel++)
        {
            uint8_t PixelData = (tile_msb & 0x01) + (tile_lsb & 0x01);
            tile_lsb >>= 1;
            tile_msb >>= 1;

            current_pixel++; // Increase the current current_pixel variable to get the accurate xPos

            m_PixelValues[((m_ScanlineCount * 256 * 4) + (current_pixel * 4))] = PixelData;
            m_FrameBufferA[((m_ScanlineCount * 160 * 4) + (current_pixel * 4))] = GetColor(m_PixelValues, current_pixel);
        }
        UpdateScreen(m_FrameBufferA.get(), (sizeof(uint8_t) * 4));
    }
}

void LCD::DrawOBJ()
{
}
uint8_t LCD::GetColor(uint8_t array[], uint8_t x)
{

    uint8_t pixel = array[((m_ScanlineCount * 256 * 4) + (x * 4))];
    switch (pixel)
    {
    case 0:
        return 0xFF;
        break;
    case 1:
        return 0xCC;
        break;
    case 2:
        return 0x77;
        break;
    case 3:
        return 0x00;
        break;
    default:
        return 0x00;
        break;
    }
}
void LCD::UpdateScreen(const void *pixeldata, int size)
{
    SDL_UpdateTexture(texture, nullptr, pixeldata, size);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}
