#include "game/elements/flight_track.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace game
{
namespace elements
{

FlightTrack::FlightTrack()
    : core::engine::IGameElement()
{}

FlightTrack::~FlightTrack() {}

void FlightTrack::draw()
{
    glLineWidth(5.0f);
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_LINES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();
}

void FlightTrack::update() {}

} // namespace elements
} // namespace game