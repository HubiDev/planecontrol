#ifndef CORE_UI_MOUSE_HPP_INCLUDED
#define CORE_UI_MOUSE_HPP_INCLUDED

#include "core/ui/mouse_event_args.hpp"

#include <SDL2/SDL.h>
#include <functional>
#include <queue>
#include <tuple>
#include <vector>

namespace core
{
namespace ui
{
// forward declarations
class IMouseAware;

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
    void handleDownEvent(IMouseAware& f_element);
    void handleUpEvent(IMouseAware& f_element);

    MouseEventArgs createEventArgs(const std::tuple<int32_t, int32_t>& f_position);

    bool m_isPressed;
    bool m_wasDown;
    bool m_wasUp;
    std::tuple<int32_t, int32_t> m_downPosition;
    std::tuple<int32_t, int32_t> m_upPosition;
    std::vector<std::reference_wrapper<IMouseAware>> m_awareElements;
    std::vector<std::tuple<int32_t, int32_t>> m_lastPositions;
};

} // namespace ui
} // namespace core

#endif // CORE_UI_MOUSE_HPP_INCLUDED
