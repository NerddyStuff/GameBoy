#include "sdl_graphics.h"
#include "bus.h"
#include "Z80g.h"
#include "cartridge.h"

Bus GameBoy;
int main(int argc, char *argv[])
{

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
    printf("Gameboy Terminated\n");

    return 0;
}
