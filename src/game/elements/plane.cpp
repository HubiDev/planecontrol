#include "game/elements/plane.hpp"

namespace game
{
namespace elements
{

Plane::Plane(std::shared_ptr<FlightTrack> f_flightTrack_p)
    : m_flightTrack_p(std::move(f_flightTrack_p))
{}

Plane::~Plane() {}

/// @brief
void Plane::load() {}

/// @brief
void Plane::update() {}

void Plane::draw() {}

void Plane::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs) {}

FlightTrack& Plane::getFlightTrack()
{
    return *m_flightTrack_p;
}

} // namespace elements

} // namespace game
