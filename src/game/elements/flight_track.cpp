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
{}

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