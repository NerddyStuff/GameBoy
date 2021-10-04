#include "bus.h"
#include "Z80g.h"
#include "cartridge.h"

bool quit = false;

int main(int argc, char* argv[])
{
    Bus GameBoy;
    
    std::shared_ptr<Cartridge> cart;
    const char* filename = argv[1];
    cart = std::make_shared<Cartridge>(filename);
    GameBoy.InsertGame(cart);
    

    while (!quit)
    {
        
        GameBoy.BusClock();
        

    }
    
    return 0;
    
}
        
    

