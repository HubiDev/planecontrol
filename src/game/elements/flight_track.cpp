#include "game/elements/flight_track.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace game
{
namespace elements
{

FlightTrack::FlightTrack()
    : core::engine::IGameElement()
    , m_line()
{
    // m_line.addPoint({10.f, 10.f});
    // m_line.addPoint({100.f, 10.f});
    // m_line.addPoint({100.f, 100.f});
    // m_line.addPoint({175.f, 120.f});
}

FlightTrack::~FlightTrack() {}

void FlightTrack::draw()
{
    m_line.draw();
}

void FlightTrack::update() {}

void FlightTrack::onMouseButtonPressed(const core::ui::MousePressedEventArgs& f_eventArgs)
{
    m_line.addPoint({static_cast<float>(f_eventArgs.m_posX), static_cast<float>(f_eventArgs.m_posY)});
}

} // namespace elements
} // namespace game