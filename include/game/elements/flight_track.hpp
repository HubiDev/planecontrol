#ifndef GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
#define GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED

#include "core/engine/game_element.hpp"

namespace game
{
namespace elements
{
class FlightTrack : public core::engine::IGameElement
{

public:
    FlightTrack();
    ~FlightTrack();

    void draw(const core::ui::Renderer& f_renderer) override;
    void update() override;

private:
    
};

} // namespace elements
} // namespace game

#endif // GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
