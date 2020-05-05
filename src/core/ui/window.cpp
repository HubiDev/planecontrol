#include "core/ui/window.hpp"
#include "SDL2/SDL_opengl.h"

namespace core
{
namespace ui
{

Window::Window(const std::string& f_title, int32_t f_width, int32_t f_height)
    : m_title(f_title)
    , m_width(f_width)
    , m_height(f_height)
    , m_window_p(nullptr)
    , m_openGlContext(nullptr)
{}

Window::~Window()
{
    SDL_GL_DeleteContext(m_openGlContext);
}

void Window::initialize()
{
    createWindow();
    createOpenGlContext();
}

SDL_Window& Window::getSDLWindow()
{
    return *m_window_p;
}

void Window::createWindow()
{
    glEnable(GL_MULTISAMPLE);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    m_window_p = std::unique_ptr<SDL_Window, SdlDeleter>(SDL_CreateWindow(m_title.c_str(),
                                                                          SDL_WINDOWPOS_CENTERED,
                                                                          SDL_WINDOWPOS_CENTERED,
                                                                          m_width,
                                                                          m_height,
                                                                          SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE));

    if(nullptr == m_window_p)
    {
        throw std::runtime_error("Failed to create window");
    }
}

void Window::createOpenGlContext()
{
    m_openGlContext = SDL_GL_CreateContext(m_window_p.get());
    glOrtho(0.f, (double)m_width, (double)m_height, 0.f, 0.f, 1.f);

    if(nullptr == m_openGlContext)
    {
        throw std::runtime_error("OpenGL not available");
    }
}

} // namespace ui
} // namespace core
