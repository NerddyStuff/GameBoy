#include "bus.h"

int main(int argc, char *argv[])
{
    Bus GameBoy;
    std::shared_ptr<Cartridge> cart;
    const char *filename = argv[1];
    cart = std::make_shared<Cartridge>(filename);
    GameBoy.InsertGame(cart);
    GameBoy.BusReset();

    bool loop = true;
    while (loop)
    {
        GameBoy.BusClock();
        GameBoy.UpdateKeys(loop);
    }

    GameBoy.~Bus();

    SDL_Log("Gameboy Terminated");
    SDL_Quit();
    return 0;
}
