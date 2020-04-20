#include "core/ui/mouse.hpp"
#include <iostream>

namespace core
{
namespace ui
{

Mouse::Mouse()
    : m_isPressed(false)
    , m_lastPosX(0)
    , m_lastPosY(0)
    , m_awareElements()
{}

Mouse::~Mouse() {}

void Mouse::registerAwareElement(IMouseAware& f_element)
{
    m_awareElements.push_back(std::reference_wrapper<IMouseAware>(f_element));
}

void Mouse::update()
{
    if(m_isPressed)
    {
        std::cout << "mouse pressed\n";
    }

    for(auto& element : m_awareElements)
    {
        if(m_isPressed)
        {
            MousePressedEventArgs e;
            e.m_posX = m_lastPosX;
            e.m_posY = m_lastPosY;
            element.get().onMouseButtonPressed(e);
        }
    }
}

void Mouse::mouseButtonDownCallback(const SDL_MouseButtonEvent& f_event)
{
    m_isPressed = true;
    m_lastPosX = f_event.x;
    m_lastPosY = f_event.y;
}

void Mouse::mouseButtonUpCallback(const SDL_MouseButtonEvent& f_event)
{
    m_isPressed = false;
    m_lastPosX = f_event.x;
    m_lastPosY = f_event.y;
}

void Mouse::mouseMoveCallback(const SDL_MouseMotionEvent& f_event)
{
    m_lastPosX = f_event.x;
    m_lastPosY = f_event.y;
}

} // namespace ui
} // namespace core