#ifndef GAME_ELEMENTS_PLANE_HPP_INLUDED
#define GAME_ELEMENTS_PLANE_HPP_INLUDED

#include "core/engine/game_element.hpp"
#include "game/elements/flight_track.hpp"

namespace game
{
namespace elements
{

class Plane : public core::engine::IGameElement
{
public:
    Plane(std::shared_ptr<FlightTrack> f_flightTrack_p);
    ~Plane();

    /// @brief
    virtual void load() override;

    /// @brief
    virtual void update() override;

    /// @brief
    virtual void draw() override;

    /// @brief
    virtual void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs) override;

    FlightTrack& getFlightTrack();

private:

    std::shared_ptr<FlightTrack> m_flightTrack_p;
};

} // namespace elements
} // namespace game

#endif