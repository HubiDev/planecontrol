// ------------------------------------------------------------------------
// This file is part of planecontrol.

// planecontrol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// planecontrol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with planecontrol.  If not, see <http://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------

#ifndef GAME_ELEMENTS_PLANE_HPP_INLUDED
#define GAME_ELEMENTS_PLANE_HPP_INLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/animation.hpp"
#include "core/graphics/texture.hpp"
#include "game/elements/flight_track.hpp"

#include <functional>

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

    /// @brief
    virtual void onMouseUp(const core::ui::MouseEventArgs& f_eventArgs) override;

    FlightTrack& getFlightTrack();

    void setLandingPointFunc(std::function<bool(const Vector&)> f_func);

private:
    Vector centrifyPoint(const Vector& f_point);
    void updatePosition(const core::engine::UpdateContext& f_context);
    void updateRotation(const core::engine::UpdateContext& f_context);
    void updateSize();
    float calcTargetRotation();
    float rotateSmooth(float f_targetRotation, const core::engine::UpdateContext& f_context);
    float calcRotationSpeed(float f_angleDiff, const core::engine::UpdateContext& f_context);

    std::shared_ptr<FlightTrack> m_flightTrack_p;
    std::unique_ptr<core::graphics::Texture> m_planeTexture_p;
    float m_speed;
    Vector m_textureOrientation;
    std::function<bool(const Vector&)> m_landingPointFunc;
    core::graphics::Animation m_landingAnimation;
};

} // namespace elements
} // namespace game

#endif