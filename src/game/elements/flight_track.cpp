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
{}

FlightTrack::~FlightTrack() {}

void FlightTrack::load()
{
    m_line_p = std::unique_ptr<core::graphics::Polyline>(new core::graphics::Polyline(TRACK_THICKNESS));    
    
    //m_line_p->push_front({240.f, 40.f});
    //m_line_p->push_front({220.f, 20.f});
    //m_line_p->push_front({120.f, 20.f});
    //m_line_p->push_front({20.f, 20.f});
}

void FlightTrack::draw()
{
    m_line_p->draw();
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
    if(m_line_p->getPointCount() == 1)
    {
        return &m_line_p->getPoint(0);
    }
    else if(m_line_p->getPointCount() > 1)
    {
        // TODO encapsulate
        auto distanceToNext = calcDistanceToNextPoint();

        if(distanceToNext > f_distance)
        {
            auto& start = m_line_p->getPoint(0);
            auto& end = m_line_p->getPoint(1);
            auto direction = core::graphics::geometry::calcDirection(start, end);

            auto distanceFactor = (f_distance / distanceToNext);
            auto shiftX = (direction.x * distanceFactor);
            auto shiftY = (direction.y * distanceFactor);

            core::graphics::Vector shiftedPoint = {(start.x + shiftX), (start.y + shiftY)};
            
            std::cout << "removed: " << m_line_p->getPoint(0).x << ", " << m_line_p->getPoint(0).y << std::endl;
            m_line_p->removePoint(0);
            m_line_p->push_front(shiftedPoint);
        }
        else
        {
            // TODO
            m_line_p->removePoint(0);
        }

        return &m_line_p->getPoint(0);
    }

    return nullptr;
}

const core::graphics::Vector* FlightTrack::getPoint(int32_t f_index)
{
    if(m_line_p->getPointCount() > 0)
    {
        return &(m_line_p->getPoint(f_index));
    }
    return nullptr;
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