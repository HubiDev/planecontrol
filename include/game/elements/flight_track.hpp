#ifndef GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
#define GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/polyline.hpp"

namespace game
{
namespace elements
{
class FlightTrack : public core::engine::IGameElement
{

public:
    FlightTrack();
    ~FlightTrack();

    void draw() override;
    void update() override;

    void onMouseButtonPressed(const core::ui::MousePressedEventArgs& f_eventArgs) override;

private:
    core::graphics::Polyline m_line;
};

} // namespace elements
} // namespace game

#endif // GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
