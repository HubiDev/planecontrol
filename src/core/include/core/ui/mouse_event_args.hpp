#ifndef CORE_UI_MOUSE_EVENT_ARGS_HPP_INCLUDED
#define CORE_UI_MOUSE_EVENT_ARGS_HPP_INCLUDED

#include <stdint.h>

namespace core
{
namespace ui
{

enum class MouseButton
{
    left,
    right,
    middle
};

struct MouseEventArgs
{
    int32_t m_posX;
    int32_t m_posY;
    MouseButton m_button;
};

} // namespace ui
} // namespace core

#endif