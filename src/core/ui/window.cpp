#include "core/ui/window.hpp"

namespace core
{
namespace ui
{

Window::Window(const std::string &f_title, int32_t f_width, int32_t f_height)
    : m_title(f_title),
      m_width(f_width),
      m_height(f_height),
      m_window_p(SDL_CreateWindow(m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL))
{
    if (nullptr == m_window_p)
    {
        throw std::runtime_error("Failed to create window");
    }
}

} // namespace ui
} // namespace core
