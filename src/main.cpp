#include "sdl_graphics.h"
#include "bus.h"
#include "Z80g.h"
#include "cartridge.h"

Bus GameBoy;

int main(int argc, char *argv[])
{

    int scale = 3;
    auto size = sizeof(uint32_t) * 160;
    std::shared_ptr<Cartridge> cart;
    const char *filename = argv[1];
    cart = std::make_shared<Cartridge>(filename);
    GameBoy.InsertGame(cart);
    GameBoy.BusReset();

    Graphics *MainWindow = new Graphics(scale);
    // SDL_Init(SDL_INIT_VIDEO);
    // SDL_Window *w = SDL_CreateWindow("awd", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160 * scale, 144 * scale, SDL_WINDOW_SHOWN);
    // SDL_Renderer *r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);
    // SDL_Texture *t = SDL_CreateTexture(r, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);
    // SDL_UpdateTexture(t, nullptr, GameBoy.m_Screen.FrameBuffer.get(), size);

    // SDL_RenderClear(r);
    // SDL_RenderCopy(r, t, nullptr, nullptr);
    // SDL_RenderPresent(r);

    bool loop = true;

    while (loop)
    {

        MainWindow->UpdateKeys(loop);
        GameBoy.BusClock();
        if (GameBoy.m_Screen.LCD_Control.LCD_Enable == 1)
        {
            MainWindow->UpdateScreen(GameBoy.m_Screen.FrameBuffer.get(), size);
        }
    }

    MainWindow->~Graphics();
    GameBoy.~Bus();
    delete MainWindow;

    std::cout << "GameBoy Terminated\n";

    return 0;
}
