#ifndef CORE_UI_MOUSE_AWARE_HPP_INCLUDED
#define CORE_UI_MOUSE_AWARE_HPP_INCLUDED

namespace core
{
namespace ui
{

// forward declarations
struct MouseEventArgs;

class IMouseAware
{
public:
    virtual ~IMouseAware() {}

    IMouseAware(const IMouseAware&) = delete;
    IMouseAware(IMouseAware&&) = delete;
    IMouseAware& operator=(const IMouseAware&) = delete;
    IMouseAware& operator=(IMouseAware&&) = delete;

    virtual void onMouseButtonPressed(const MouseEventArgs& f_eventArgs) {}
    virtual void onMouseDown(const MouseEventArgs& f_eventArgs) {}
    virtual void onMouseUp(const MouseEventArgs& f_eventArgs) {}

protected:
    IMouseAware() {}
};

} // namespace ui
} // namespace core

#endif // CORE_UI_MOUSE_AWARE_HPP_INCLUDED
