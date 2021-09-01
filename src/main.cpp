#include <SDL2/SDL.h>
#include "bus.h"
#include "gameboy.h"

int main(int argc, char** args)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDLK_w:
            
            break;
        
        default:
            break;
        }
    }
    

    

    
    return 0;
    
}
        
    

