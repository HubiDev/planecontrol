#include "SDL2/SDL.h"
#include <stdio.h>
#include "core/ui/window.hpp"
#include "core/ui/sdl_context.hpp"

int main(int argc, const char *argv[])
{
    core::ui::SdlContext sdlContext;

    auto window = core::ui::Window("Plane Control", 1280, 720);

    bool quit = false;

    while (!quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    return 0;
}