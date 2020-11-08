#ifndef CORE_UI_SDL_DELETER_HPP_INCLUDED
#define CORE_UI_SDL_DELETER_HPP_INCLUDED

#include <SDL2/SDL.h>

namespace core
{
namespace ui
{
struct SdlDeleter
{
    void operator()(SDL_Window* f_window_p) const
    {
        SDL_DestroyWindow(f_window_p);
    }

    void operator()(SDL_Renderer* f_renderer_p) const
    {
        SDL_DestroyRenderer(f_renderer_p);
    }
};

} // namespace ui

} // namespace core

#endif
