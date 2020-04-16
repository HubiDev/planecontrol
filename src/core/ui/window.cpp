#include "core/ui/window.hpp"

namespace core
{
namespace ui
{

Window::Window(const std::string& f_title, int32_t f_width, int32_t f_height)
    : m_title(f_title)
    , m_width(f_width)
    , m_height(f_height)
    , m_window_p(nullptr)
    , m_renderer_p(nullptr)
{}

void Window::initialize()
{
    createWindow();
    createRenderer();
}

const Renderer& Window::getRenderer() const
{
    return *m_renderer_p;
}

void Window::createWindow() 
{
    m_window_p = std::unique_ptr<SDL_Window, SdlDeleter>(SDL_CreateWindow(
        m_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL));

    if(nullptr == m_window_p)
    {
        throw std::runtime_error("Failed to create window");
    }
}

void Window::createRenderer()
{
    if(nullptr != m_window_p)
    {
        m_renderer_p =
            std::unique_ptr<Renderer>(new Renderer(SDL_CreateRenderer(m_window_p.get(), -1, SDL_RENDERER_ACCELERATED)));
    }
    else
    {
        throw std::runtime_error("Window not available to create renderer");
    }
}

} // namespace ui
} // namespace core
