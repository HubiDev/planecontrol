#include "game/elements/plane.hpp"
#include <iostream>

namespace game
{
namespace elements
{

Plane::Plane(std::shared_ptr<FlightTrack> f_flightTrack_p)
    : m_flightTrack_p{std::move(f_flightTrack_p)}
    , m_planeTexture_p{}
    , m_speed{2.f}
{}

Plane::~Plane() {}

/// @brief
void Plane::load()
{
    m_planeTexture_p =
        std::unique_ptr<core::graphics::Rectangle>(new core::graphics::Rectangle({10.f, 10.f}, {50.f, 50.f}));
}

/// @brief
void Plane::update(const core::engine::UpdateContext& f_context)
{
    //std::cout << "Duration: " << f_context.m_durationSinceLastUpdate << std::endl;

    if(m_flightTrack_p->isActive())
    {
        if(m_flightTrack_p->calcDistanceToNextPoint() > m_speed)
        {
            std::cout << m_flightTrack_p->calcDistanceToNextPoint() << std::endl;
        }

        auto point_p = m_flightTrack_p->moveToNextPoint(m_speed);

        if(nullptr != point_p)
        {
            m_planeTexture_p->setPosition(point_p->x, point_p->y);
        }
    }
}

void Plane::draw()
{
    m_planeTexture_p->draw();
}

void Plane::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs)
{
    m_flightTrack_p->clear();
    m_flightTrack_p->setActive(true);
}

FlightTrack& Plane::getFlightTrack()
{
    return *m_flightTrack_p;
}

} // namespace elements

} // namespace game
