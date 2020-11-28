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

#include "game/elements/flight_track.hpp"
#include "core/graphics/geometry.hpp"
#include "core/ui/mouse_event_args.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <iostream>

namespace game
{
namespace elements
{

FlightTrack::FlightTrack()
    : core::engine::IGameElement()
    , m_line_p(nullptr)
    , m_isActive(false)
    , m_isVisible(true)
{}

FlightTrack::~FlightTrack() {}

void FlightTrack::load()
{
    m_line_p = std::unique_ptr<core::graphics::Polyline>(new core::graphics::Polyline(TRACK_THICKNESS));
}

void FlightTrack::draw()
{
    if(m_isVisible)
    {
        m_line_p->draw();
    }
}

void FlightTrack::update(const core::engine::UpdateContext& f_context) {}

void FlightTrack::setActive(bool f_isActive)
{
    m_isActive = f_isActive;
}

bool FlightTrack::isActive()
{
    return m_isActive;
}

void FlightTrack::clear()
{
    m_line_p->reset();
}

const core::graphics::Vector* FlightTrack::moveToNextPoint(float f_distance)
{
    // jump to last point
    if(m_line_p->getPointCount() == 1)
    {
        return &m_line_p->getPoint(0);
    }
    else if(m_line_p->getPointCount() > 1)
    {
        auto distanceToNext = calcDistanceToNextPoint();

        // distance to next is larger than the distance to cover
        if(distanceToNext > f_distance)
        {
            shiftStart(f_distance, distanceToNext);
        }
        // distance to next is smaller
        else if(distanceToNext < f_distance)
        {
            float remainingDistance = {f_distance - distanceToNext};

            // Remove points until distance is covered
            do
            {
                m_line_p->removePoint(0);
                distanceToNext = calcDistanceToNextPoint();
                remainingDistance -= distanceToNext;
            } while((remainingDistance > 0.f) && (m_line_p->getPointCount() > 1));

            // Recalculate what distance is still left
            remainingDistance += distanceToNext;

            shiftStart(remainingDistance, distanceToNext);
        }
        // distance matches perfectly
        else
        {
            m_line_p->removePoint(0);
        }

        return &m_line_p->getPoint(0);
    }

    return nullptr;
}

void FlightTrack::shiftStart(float f_distanceToShift, float f_distanceToNext)
{
    auto& start = m_line_p->getPoint(0);
    auto& end = m_line_p->getPoint(1);
    auto direction = core::graphics::geometry::calcDirection(start, end);

    auto distanceFactor = (f_distanceToNext / f_distanceToShift);
    auto shiftX = (direction.x / distanceFactor);
    auto shiftY = (direction.y / distanceFactor);

    core::graphics::Vector shiftedPoint = {(start.x + shiftX), (start.y + shiftY)};

    m_line_p->removePoint(0);
    m_line_p->push_front(shiftedPoint);
}

float FlightTrack::getRemainingLength()
{
    return m_line_p->getLength();
}

void FlightTrack::setVisible(bool f_visible)
{
    m_isVisible  = f_visible;
}

const core::graphics::Vector* FlightTrack::getPoint(int32_t f_index)
{
    if(m_line_p->getPointCount() > 0)
    {
        return &(m_line_p->getPoint(f_index));
    }
    return nullptr;
}

core::graphics::Vector FlightTrack::getDirection()
{
    if(m_line_p->getPointCount() >= 2)
    {
        return core::graphics::geometry::calcDirection(m_line_p->getPoint(0), m_line_p->getPoint(1));
    }

    return core::graphics::Vector{}; //TODO
}

void FlightTrack::setPoints(const std::vector<core::graphics::Vector>& f_points)
{
    for(auto& current : f_points)
    {
        m_line_p->push_back(current);
    }
}

void FlightTrack::onMouseButtonPressed(const core::ui::MouseEventArgs& f_eventArgs)
{
    if(m_isActive)
    {
        m_line_p->push_back({static_cast<float>(f_eventArgs.m_posX), static_cast<float>(f_eventArgs.m_posY)});
    }
}

float FlightTrack::calcDistanceToNextPoint() const
{
    if(m_line_p->getPointCount() >= 2)
    {
        auto& start = m_line_p->getPoint(0);
        auto& end = m_line_p->getPoint(1);

        return core::graphics::geometry::calcDistance(start, end);
    }

    return 0.0;
    //throw new std::runtime_error("flight track has not enough points");
}

} // namespace elements
} // namespace game