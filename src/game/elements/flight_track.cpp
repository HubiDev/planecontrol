#include "game/elements/flight_track.hpp"
#include <SDL2/SDL.h>

namespace game
{
namespace elements
{

FlightTrack::FlightTrack()
    : core::engine::IGameElement()
{}

FlightTrack::~FlightTrack() {}

void FlightTrack::draw(const core::ui::Renderer& f_renderer)
{
    SDL_SetRenderDrawColor(&f_renderer.getRenderer(), 128, 128, 128, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(&f_renderer.getRenderer(), 10, 10, 400, 400);
}

void FlightTrack::update()
{

}

} // namespace elements
} // namespace game