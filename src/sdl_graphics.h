#include <SDL2/SDL.h>

class Graphics
{
private:

    SDL_Window *window{};
    SDL_Texture *texture{};
    SDL_Renderer *renderer{};
    

public:
    Graphics(int scale);
    ~Graphics();

    void UpdateScreen(const void* pixeldata, int size);
    void UpdateKeys(bool &quit);
};

