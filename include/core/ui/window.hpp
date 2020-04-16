#ifndef CORE_UI_WINDOW_HPP_INCLUDED
#define CORE_UI_WINDOW_HPP_INCLUDED

#include "SDL2/SDL.h"
#include <memory>
#include <string>

#include "core/ui/renderer.hpp"
#include "sdl_deleter.hpp"

namespace core
{
namespace ui
{
class Window
{
public:
    Window(const std::string& f_title, int32_t f_width, int32_t f_height);
    void initialize();
    const Renderer& getRenderer() const;

private:

    void createWindow();
    void createRenderer();

    std::string m_title;
    int32_t m_width;
    int32_t m_height;
    std::unique_ptr<SDL_Window, SdlDeleter> m_window_p;
    std::unique_ptr<Renderer> m_renderer_p;
};

} // namespace ui

} // namespace core

#endif