#ifndef GAME_ELEMENTS_PLANE_HPP_INLUDED
#define GAME_ELEMENTS_PLANE_HPP_INLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/texture.hpp"
#include "game/elements/flight_track.hpp"

namespace game
{
namespace elements
{

using core::graphics::Vector;

class Plane : public core::engine::IGameElement
{
public:
    Plane(std::shared_ptr<FlightTrack> f_flightTrack_p);
    ~Plane();

    /// @brief
    virtual void load() override;

    /// @brief
    virtual void update(const core::engine::UpdateContext& f_context) override;

    /// @brief
    virtual void draw() override;

    /// @brief
    virtual void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs) override;

    FlightTrack& getFlightTrack();

private:
    Vector centrifyPoint(const Vector& f_point);
    void updatePosition();
    void updateRotation();
    float calcTargetRotation();
    float rotateSmooth(float f_targetRotation);
    float calcRotationSpeed(float f_angleDiff);

    std::shared_ptr<FlightTrack> m_flightTrack_p;
    std::unique_ptr<core::graphics::Texture> m_planeTexture_p;
    float m_speed;
    Vector m_textureOrientation;
};

} // namespace elements
} // namespace game

#endif