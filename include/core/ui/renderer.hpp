#ifndef CORE_UI_RENDERER_HPP_INCLUDED
#define CORE_UI_RENDERER_HPP_INCLUDED

#include "core/ui/sdl_deleter.hpp"
#include <SDL2/SDL.h>
#include <memory>

namespace core
{
namespace ui
{
class Renderer
{
public:
    explicit Renderer(SDL_Renderer* f_renderer_p);
    ~Renderer();

    void prepareRendering() const;
    void finishRendering() const;
    SDL_Renderer& getRenderer() const;

private:
    std::unique_ptr<SDL_Renderer, SdlDeleter> m_renderer_p;
};

} // namespace ui
} // namespace core

#endif
