#include "SDL2/SDL.h"
#include <stdio.h>
#include "core/ui/window.hpp"

int main(int argc, const char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO); // Initialize SDL2

    auto window = core::ui::Window("Plane Control", 1280, 720);

    bool quit = false;

    // The window is open: could enter program loop here (see SDL_PollEvent())
    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    // Clean up
    SDL_Quit();
    return 0;
}