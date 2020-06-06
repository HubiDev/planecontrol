#include "game/elements/flight_track.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

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
    // m_line_p->addPoint({20.f, 20.f});
    // m_line_p->addPoint({120.f, 20.f});
    // m_line_p->addPoint({220.f, 20.f});
}

void FlightTrack::draw()
{
    m_line_p->draw();
}

void FlightTrack::update() {}

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

void FlightTrack::onMouseButtonPressed(const core::ui::MouseEventArgs& f_eventArgs)
{
    if(m_isActive)
    {
        m_line_p->addPoint({static_cast<float>(f_eventArgs.m_posX), static_cast<float>(f_eventArgs.m_posY)});
    }
}

} // namespace elements
} // namespace game