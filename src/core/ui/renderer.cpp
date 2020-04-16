#include "core/ui/renderer.hpp"

namespace core
{
namespace ui
{

Renderer::Renderer(SDL_Renderer* f_renderer_p)
    : m_renderer_p(f_renderer_p)
{}

Renderer::~Renderer() {}

void Renderer::prepareRendering() const
{
    SDL_RenderClear(m_renderer_p.get());
}

void Renderer::finishRendering() const
{
    SDL_RenderPresent(m_renderer_p.get());
}

} // namespace ui

} // namespace core