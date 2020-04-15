#include "core/ui/sdl_context.hpp"
#include <SDL2/SDL.h>

namespace core
{
namespace ui
{

SdlContext::SdlContext()
{
    SDL_Init(SDL_INIT_VIDEO);
}

SdlContext ::~SdlContext()
{
    SDL_Quit();
}

} // namespace ui
} // namespace core