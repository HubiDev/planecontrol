#include "SDL2/SDL.h"
#include <stdio.h>
#include "core/ui/window.hpp"
#include "core/ui/sdl_context.hpp"
#include "core/ui/event_manager.hpp"

int main(int argc, const char *argv[])
{
    core::ui::SdlContext sdlContext;

    auto window = core::ui::Window("Plane Control", 1280, 720);
    auto eventManager = core::ui::EventManager();
    bool quit = false;
    eventManager.addEventCallback(SDL_QUIT, [&quit](const SDL_Event& f_event) -> void
    {
        quit = true;
    });    

    while (!quit)
    {
        eventManager.processEvents();
    }

    return 0;
}