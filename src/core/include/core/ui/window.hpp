// ------------------------------------------------------------------------
// This file is part of planecontrol.

// planecontrol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// planecontrol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with planecontrol.  If not, see <http://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------

#ifndef CORE_UI_WINDOW_HPP_INCLUDED
#define CORE_UI_WINDOW_HPP_INCLUDED

#include "SDL2/SDL.h"
#include <memory>
#include <string>

#include "sdl_deleter.hpp"

namespace core
{
namespace ui
{
class Window
{
public:
    Window(const std::string& f_title, int32_t f_width, int32_t f_height);
    ~Window();
    void initialize();
    SDL_Window& getSDLWindow();

private:

    void createWindow();
    void createOpenGlContext();

    std::string m_title;
    int32_t m_width;
    int32_t m_height;
    std::unique_ptr<SDL_Window, SdlDeleter> m_window_p;
    SDL_GLContext m_openGlContext;
};

} // namespace ui

} // namespace core

#endif