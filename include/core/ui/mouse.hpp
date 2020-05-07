#ifndef CORE_UI_MOUSE_HPP_INCLUDED
#define CORE_UI_MOUSE_HPP_INCLUDED

#include "core/ui/mouse_aware.hpp"
#include <SDL2/SDL.h>
#include <functional>
#include <vector>
#include <queue>
#include <tuple>

namespace core
{
namespace ui
{
class Mouse
{
public:
    Mouse();
    ~Mouse();

    void registerAwareElement(IMouseAware& f_element);

    void update();

    void mouseButtonDownCallback(const SDL_MouseButtonEvent& f_event);
    void mouseButtonUpCallback(const SDL_MouseButtonEvent& f_event);
    void mouseMoveCallback(const SDL_MouseMotionEvent& f_event);
    

private:

    void handlePressedEvent(IMouseAware& f_element);

    bool m_isPressed;
    bool m_wasClicked;
    std::vector<std::reference_wrapper<IMouseAware>> m_awareElements;
    std::vector<std::tuple<int32_t, int32_t>> m_lastPositions;
};

} // namespace ui
} // namespace core

#endif // CORE_UI_MOUSE_HPP_INCLUDED
