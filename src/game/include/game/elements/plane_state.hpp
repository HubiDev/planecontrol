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

#ifndef GAME_ELEMENTS_PLANE_STATE_HPP_INCLUDED
#define GAME_ELEMENTS_PLANE_STATE_HPP_INCLUDED

#include "core/engine/update_context.hpp"
#include "core/graphics/animation.hpp"
#include "core/graphics/vector.hpp"
#include "core/ui/mouse_event_args.hpp"

#include <vector>

namespace game
{
namespace elements
{

class Plane;

class PlaneState
{
public:
    PlaneState(PlaneState* f_next);
    virtual ~PlaneState() = default;

    virtual void updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane) = 0;
    virtual void updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane) = 0;
    virtual void updateSize(Plane& f_plane) = 0;

    virtual PlaneState* checkForNextState(Plane& f_plane) = 0;

    virtual void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) = 0;
    virtual void onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) = 0;
    virtual void onStateChange(const PlaneState& f_callingState, Plane& f_plane) {}

protected:
    PlaneState* m_next;
};

class PlaneStateFlying : public PlaneState
{
public:
    PlaneStateFlying(PlaneState* f_next);

    void updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane) final;
    void updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane) final;
    void updateSize(Plane& f_plane) final;

    PlaneState* checkForNextState(Plane& f_plane) final;

    void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) final;
    void onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) final;

private:
    bool m_switchToNextState;
};

class PlaneStateLanding : public PlaneState
{
public:
    PlaneStateLanding(PlaneState* f_next);

    void updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane) final;
    void updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane) final;
    void updateSize(Plane& f_plane) final;

    PlaneState* checkForNextState(Plane& f_plane) final;

    void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) final;
    void onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) final;

    void setLandingPath(const std::vector<core::graphics::Vector>& f_path);
    void onStateChange(const PlaneState& f_callingState, Plane& f_plane) final;

private:
    core::graphics::Animation m_landingAnimation;
    core::graphics::Animation m_slowDownAnimation;
    std::vector<core::graphics::Vector> m_landingPath;
    bool m_switchToNextState;
};

class PlaneStateTaxiingToGate : public PlaneState
{
public:
    PlaneStateTaxiingToGate(PlaneState* f_next);

    void updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane) final;
    void updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane) final;
    void updateSize(Plane& f_plane) final;

    PlaneState* checkForNextState(Plane& f_plane) final;

    void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) final;
    void onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) final;

    void startParking(const std::vector<core::graphics::Vector>& f_path, Plane& f_plane);
private:
    bool m_parkingHasStarted;
};

} // namespace elements
} // namespace game

#endif