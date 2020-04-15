#ifndef CORE_UI_WINDOW_HPP_INCLUDED
#define CORE_UI_WINDOW_HPP_INCLUDED

#include "SDL2/SDL.h"
#include <memory>
#include <string>

namespace core
{
namespace ui
{
class Window
{
public:
    Window();

private:

    std::unique_ptr<SDL_Window> m_window_p;

};

} // namespace ui

} // namespace core

#endif