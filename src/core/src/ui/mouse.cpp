// ------------------------------------------------------------------------
// This file is part of planecontrol.

// planecontrol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// planecontrol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with planecontrol.  If not, see <http://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------

#include "core/ui/mouse.hpp"
#include "core/ui/mouse_event_args.hpp"
#include "core/ui/mouse_aware.hpp"

namespace core
{
namespace ui
{

Mouse::Mouse()
    : m_isPressed(false)
    , m_wasDown(false)
    , m_wasUp(false)
    , m_downPosition(0, 0)
    , m_upPosition(0, 0)
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
        handleDownEvent(element);
        handleUpEvent(element);
    }

    // clear the queue
    m_lastPositions.clear();
    m_wasDown = false;
    m_wasUp = false;
}

void Mouse::handlePressedEvent(IMouseAware& f_element)
{
    if(m_isPressed)
    {
        for(const auto& position : m_lastPositions)
        {
            f_element.onMouseButtonPressed(createEventArgs(position));
        }
    }
}

void Mouse::handleDownEvent(IMouseAware& f_element)
{
    if(m_wasDown)
    {
        f_element.onMouseDown(createEventArgs(m_downPosition));
    }
}

void Mouse::handleUpEvent(IMouseAware& f_element) 
{
    if(m_wasUp)
    {
        f_element.onMouseUp(createEventArgs(m_upPosition));
    }
}

MouseEventArgs Mouse::createEventArgs(const std::tuple<int32_t, int32_t>& f_position)
{
    return {std::get<0>(f_position), std::get<1>(f_position)};
}

void Mouse::mouseButtonDownCallback(const SDL_MouseButtonEvent& f_event)
{
    m_wasDown = true;
    m_downPosition = {f_event.x, f_event.y};

    m_isPressed = true;
    m_lastPositions.push_back({f_event.x, f_event.y});
}

void Mouse::mouseButtonUpCallback(const SDL_MouseButtonEvent& f_event)
{
    m_wasUp = true;
    m_upPosition = {f_event.x, f_event.y};

    m_isPressed = false;
    m_lastPositions.push_back({f_event.x, f_event.y});
}

void Mouse::mouseMoveCallback(const SDL_MouseMotionEvent& f_event)
{
    m_lastPositions.push_back({f_event.x, f_event.y});
}

} // namespace ui
} // namespace core