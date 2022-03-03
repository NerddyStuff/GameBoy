#include "sdl_graphics.h"

Graphics::Graphics(int scale)
{
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("GameBoy Test Screen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 160 * scale, 144 * scale, SDL_WINDOW_SHOWN);
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
}

void Graphics::UpdateScreen(const void *pixeldata, int size)
{
    SDL_UpdateTexture(texture, nullptr, pixeldata, size);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Graphics::UpdateKeys(bool &quit)
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        switch (e.type)
        {
        case SDL_KEYDOWN:
            switch (e.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = false;
                break;

            default:
                break;
            }
            break;
        case SDL_QUIT:
            quit = false;
        default:
            break;
        }
    }
}
Graphics::~Graphics()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
