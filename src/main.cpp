#include "bus.h"
#include "gameboy.h"
#include "cartridge.h"

int main(int argc, char* argv[])
{
    Bus GameBoy;

    const char* filename = argv[2];
    GameBoy.game.LoadRom(filename);

    bool quit = false;
    while (!quit)
    {
        GameBoy.cpu.Clock();
    }
    
    return 0;
    
}
        
    

