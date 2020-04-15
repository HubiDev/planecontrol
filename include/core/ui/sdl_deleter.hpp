#ifndef CORE_UI_SDL_DELETER_HPP_INCLUDED
#define CORE_UI_SDL_DELETER_HPP_INCLUDED

#include <SDL2/SDL.h>

namespace core
{
namespace ui
{
struct SdlDeleter
{
    void operator()(SDL_Window *p) const { SDL_DestroyWindow(p); }
};

} // namespace ui

} // namespace core

#endif
