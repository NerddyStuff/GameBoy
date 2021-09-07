#include <SDL2/SDL.h>

#include "bus.h"
#include "gameboy.h"
#include "cartridge.h"

bool quit = false;

void UpdateKeys(SDL_Event e)
{
    while (SDL_PollEvent(&e))
    {
        switch(e.type)
        {
            case SDL_KEYDOWN:
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                
                default:
                    break;
                }
            }
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    Bus GameBoy;
    GameBoy.cpu.ResetCpu();

    SDL_Event e;

    const char* filename = argv[1];
    GameBoy.game.LoadRom(filename);

    while (!quit)
    {
        
        GameBoy.cpu.Clock();
        // UpdateKeys(e);

    }
    
    return 0;
    
}
        
    

