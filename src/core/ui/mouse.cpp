#include "core/ui/mouse.hpp"

namespace core
{
namespace ui
{

Mouse::Mouse()
    : m_isPressed(false)
    , m_awareElements()
    , m_lastPositions()
{}

Mouse::~Mouse() {}

void Mouse::registerAwareElement(IMouseAware& f_element)
{
    m_awareElements.push_back(std::reference_wrapper<IMouseAware>(f_element));
}

void Mouse::update()
{
    for(auto& element : m_awareElements)
    {
        handlePressedEvent(element);
    }

    // clear the queue
    m_lastPositions.clear();
}

void Mouse::handlePressedEvent(IMouseAware& f_element)
{
    if(m_isPressed)
    {
        for(const auto& position : m_lastPositions)
        {
            MousePressedEventArgs e = {std::get<0>(position), std::get<1>(position)};
            f_element.onMouseButtonPressed(e);
        }
    }
}

void Mouse::mouseButtonDownCallback(const SDL_MouseButtonEvent& f_event)
{
    m_isPressed = true;
    m_lastPositions.push_back({f_event.x, f_event.y});
}

void Mouse::mouseButtonUpCallback(const SDL_MouseButtonEvent& f_event)
{
    m_isPressed = false;
    m_lastPositions.push_back({f_event.x, f_event.y});
}

void Mouse::mouseMoveCallback(const SDL_MouseMotionEvent& f_event)
{
    m_lastPositions.push_back({f_event.x, f_event.y});
}

} // namespace ui
} // namespace core