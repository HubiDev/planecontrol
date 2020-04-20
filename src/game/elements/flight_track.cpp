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
    // TEST code
    m_line.addPoint({10.f, 10.f});
    m_line.addPoint({100.f, 100.f});

}

FlightTrack::~FlightTrack() {}

void FlightTrack::draw()
{
    m_line.draw();
}

void FlightTrack::update() {}

} // namespace elements
} // namespace game