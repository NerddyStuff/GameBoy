#include <SDL2/SDL.h>

#include "bus.h"
#include "Z80g.h"
#include "cartridge.h"

SDL_Window *window;
SDL_Texture *texture;
SDL_Renderer *renderer;
SDL_Event e;

Bus GameBoy;

auto size = sizeof(GameBoy.m_VRAM.get()[0]) * 160;

void UpdateGraphics()
{
    SDL_UpdateTexture(texture, nullptr, GameBoy.m_VRAM.get(), size);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
};

int main(int argc, char *argv[])
{
    int scale = 2;

    std::shared_ptr<Cartridge> cart;
    const char *filename = argv[1];
    cart = std::make_shared<Cartridge>(filename);
    GameBoy.InsertGame(cart);
    GameBoy.BusReset();

    //  Wrap SDL code in a function
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("GameBoy Test Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160 * scale, 144 * scale, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, 160, 144);

    bool loop = true;

    while (loop)
    {

        GameBoy.BusClock();
        UpdateGraphics();
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    loop = false;
                    break;

                default:
                    break;
                }
                break;
            case SDL_QUIT:
                loop = false;
            default:
                break;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);

    SDL_Quit();
    GameBoy.~Bus();

    std::cout << "GameBoy Terminated\n";

    return 0;
}
