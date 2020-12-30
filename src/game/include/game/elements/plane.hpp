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
#include "game/elements/plane_state.hpp"

#include <functional>
#include <tuple>

namespace game
{
namespace elements
{

using core::graphics::Vector;

class Plane : public core::engine::IGameElement
{
public:
    // Declare states as friends
    friend PlaneStateFlying;
    friend PlaneStateLanding;
    friend PlaneStateTaxiingToGate;
    friend PlaneStateTaxiingToStart;
    friend PlaneStateTakeoff;

    Plane(std::shared_ptr<FlightTrack> f_flightTrack_p, const core::graphics::Vector& f_position);
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

    /// @brief
    std::shared_ptr<FlightTrack> getFlightTrack();

    // Landing
    bool landingPointRequired();
    std::tuple<bool, core::graphics::Vector> landingPathNeedsVerify();
    void finalizeFlightTrack(bool f_valid);
    void setLandingPath(const std::vector<core::graphics::Vector>& f_path);

    // Parking
    bool parkingSlotNeedsVerify();
    void startParking(const std::vector<core::graphics::Vector>& f_path);

    // Starting
    bool startSlotNeedsVerify();
    void startTakeoff(const std::vector<core::graphics::Vector>& f_path);

    // Takeoff
    void setTakeoffPath(const std::vector<core::graphics::Vector>& f_path);

private:
    Vector centrifyPoint(const Vector& f_point);
    float calcTargetRotation();
    float rotateSmooth(float f_targetRotation, const core::engine::UpdateContext& f_context);
    float calcRotationSpeed(float f_angleDiff, const core::engine::UpdateContext& f_context);

    bool mouseHit(const core::ui::MouseEventArgs& f_eventArgs);

    std::shared_ptr<FlightTrack> m_flightTrack_p;
    std::unique_ptr<core::graphics::Texture> m_planeTexture_p;
    float m_speed;
    Vector m_textureOrientation;
    Vector m_postion;

    // States
    PlaneStateTakeoff m_takeoffState;
    PlaneStateTaxiingToStart m_taxiToStartState;
    PlaneStateTaxiingToGate m_taxiToGateState;
    PlaneStateLanding m_landingState;
    PlaneStateFlying m_flyingState;
    PlaneState* m_currentState;

    bool m_verifyFlightTrack;
    Vector m_mouseUpLocation;
    bool m_flightTrackModFinished;
    bool m_verifyParkingSlot;
    bool m_verifyStartSlot;
};

} // namespace elements
} // namespace game

#endif