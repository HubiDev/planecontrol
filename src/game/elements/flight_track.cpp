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
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);

    glLineWidth(5.0f);
    glColor3f(1.f, 1.f, 1.f);
    glBegin(GL_LINE_STRIP);
    glVertex2i(0, 0);
    glVertex2i(100, 100);
    glVertex2i(100, 100);
    glVertex2i(150, 175);
    glVertex2i(150, 175);
    glVertex2i(250, 175);
    glEnd();

    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_BLEND);
}

void FlightTrack::update() {}

} // namespace elements
} // namespace game