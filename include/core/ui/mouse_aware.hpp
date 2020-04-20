#ifndef CORE_UI_MOUSE_AWARE_HPP_INCLUDED
#define CORE_UI_MOUSE_AWARE_HPP_INCLUDED

#include "core/ui/mouse_pressed_event_args.hpp"

namespace core
{
namespace ui
{
class IMouseAware
{
public:
    virtual ~IMouseAware() {}

    IMouseAware(const IMouseAware&) = delete;
    IMouseAware(IMouseAware&&) = delete;
    IMouseAware& operator=(const IMouseAware&) = delete;
    IMouseAware& operator=(IMouseAware&&) = delete;

    virtual void onMouseButtonPressed(const MousePressedEventArgs& f_eventArgs) {}

protected:
    IMouseAware() {}
};

} // namespace ui
} // namespace core

#endif // CORE_UI_MOUSE_AWARE_HPP_INCLUDED
