#ifndef GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
#define GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/polyline.hpp"
#include <memory>

namespace game
{
namespace elements
{
class FlightTrack : public core::engine::IGameElement
{

public:
    FlightTrack();
    ~FlightTrack();

    void load() override;
    void draw() override;
    void update() override;

    void onMouseButtonPressed(const core::ui::MouseEventArgs& f_eventArgs) override;

private:
    std::unique_ptr<core::graphics::Polyline> m_line_p;
    static constexpr float TRACK_THICKNESS = 5.f;
};

} // namespace elements
} // namespace game

#endif // GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
