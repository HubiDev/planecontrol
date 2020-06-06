#include "game/elements/plane.hpp"

namespace game
{
namespace elements
{

Plane::Plane(std::shared_ptr<FlightTrack> f_flightTrack_p)
    : m_flightTrack_p(std::move(f_flightTrack_p))
    , m_planeTexture_p()
{}

Plane::~Plane() {}

/// @brief
void Plane::load()
{
    m_planeTexture_p =
        std::unique_ptr<core::graphics::Rectangle>(new core::graphics::Rectangle({10.f, 10.f}, {50.f, 50.f}));
}

/// @brief
void Plane::update()
{
    if(m_flightTrack_p->isActive())
    {
        m_planeTexture_p->move(1.f, 1.f);
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
