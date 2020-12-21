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

#include "game/elements/plane_state.hpp"
#include "core/graphics/geometry.hpp"
#include "game/elements/plane.hpp"

#include <cmath>

// DEBUGGING
#include <iostream>

namespace game
{
namespace elements
{

PlaneState::PlaneState(PlaneState* f_next)
    : m_next(f_next)
{}

PlaneStateFlying::PlaneStateFlying(PlaneState* f_next)
    : PlaneState(f_next)
    , m_switchToNextState(false)
{}

void PlaneStateFlying::updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane)
{
    auto adaptedSpeed = core::engine::adaptToFps(f_context, f_plane.m_speed);
    auto point_p = f_plane.m_flightTrack_p->moveToNextPoint(adaptedSpeed);

    if(point_p)
    {
        auto centrifiedPoint = f_plane.centrifyPoint(*point_p);
        f_plane.m_planeTexture_p->setPosition(centrifiedPoint.x, centrifiedPoint.y);
    }

    // TODO check wether plane has reached end of flight track
    if(f_plane.m_flightTrack_p->getRemainingLength() == 0.f && f_plane.m_flightTrackModFinished)
    {
        m_switchToNextState = true;
    }
}

void PlaneStateFlying::updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane)
{
    auto targetAngle = f_plane.calcTargetRotation();

    if(!std::isnan(targetAngle))
    {
        targetAngle = f_plane.rotateSmooth(targetAngle, f_context);
        f_plane.m_planeTexture_p->setRotation(targetAngle);
    }
}

void PlaneStateFlying::updateSize(Plane& f_plane) {}

void PlaneStateFlying::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane)
{
    if(f_plane.mouseHit(f_eventArgs))
    {
        f_plane.m_flightTrackModFinished = false;
        f_plane.m_flightTrack_p->clear();
        f_plane.m_flightTrack_p->setActive(true);
    }
    else
    {
        f_plane.m_flightTrack_p->setActive(false);
    }
}

void PlaneStateFlying::onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane)
{
    if(f_plane.m_flightTrack_p->isActive()) // Plane was hit on mouse down
    {
        f_plane.m_verifyFlightTrack = true;
    }
}

// TODO move this to base class
PlaneState* PlaneStateFlying::checkForNextState(Plane& f_plane)
{
    if(m_switchToNextState)
    {
        m_next->onStateChange(*this, f_plane);
        return this->m_next;
    }

    return this;
}

PlaneStateLanding::PlaneStateLanding(PlaneState* f_next)
    : PlaneState(f_next)
    , m_landingPath()
    , m_landingAnimation{400.f, 500.f, 30.f}
    , m_slowDownAnimation{100.f, 300.f, 0.5}
    , m_switchToNextState(false)
{}

void PlaneStateLanding::updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane)
{
    // Move plane
    auto adaptedSpeed = core::engine::adaptToFps(f_context, f_plane.m_speed);
    auto point_p = f_plane.m_flightTrack_p->moveToNextPoint(adaptedSpeed);

    if(point_p)
    {
        auto centrifiedPoint = f_plane.centrifyPoint(*point_p);
        f_plane.m_planeTexture_p->setPosition(centrifiedPoint.x, centrifiedPoint.y);
    }

    // speed animation
    if(m_slowDownAnimation.isActive(f_plane.m_flightTrack_p->getRemainingLength()))
    {
        auto speedDiff = m_slowDownAnimation.update(f_plane.m_flightTrack_p->getRemainingLength());
        f_plane.m_speed -= speedDiff;
    }

    // state switch
    if(f_plane.m_flightTrack_p->getRemainingLength() == 0.f)
    {
        m_switchToNextState = true;
    }
}

void PlaneStateLanding::updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane)
{
    auto targetAngle = f_plane.calcTargetRotation();

    if(!std::isnan(targetAngle))
    {
        targetAngle = f_plane.rotateSmooth(targetAngle, f_context);
        f_plane.m_planeTexture_p->setRotation(targetAngle);
    }
}

void PlaneStateLanding::updateSize(Plane& f_plane)
{
    if(m_landingAnimation.isActive(f_plane.m_flightTrack_p->getRemainingLength()))
    {
        auto sizeDiff = m_landingAnimation.update(f_plane.m_flightTrack_p->getRemainingLength());
        auto planeSize = f_plane.m_planeTexture_p->getSize();
        f_plane.m_planeTexture_p->setSize({planeSize.x - sizeDiff, planeSize.y - sizeDiff});
    }
}

void PlaneStateLanding::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) {}
void PlaneStateLanding::onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) {}

void PlaneStateLanding::setLandingPath(const std::vector<core::graphics::Vector>& f_path)
{
    m_landingPath = f_path;
}

PlaneState* PlaneStateLanding::checkForNextState(Plane& f_plane)
{
    if(m_switchToNextState)
    {
        m_next->onStateChange(*this, f_plane);
        return this->m_next;
    }

    return this;
}

void PlaneStateLanding::onStateChange(const PlaneState& f_callingState, Plane& f_plane)
{
    static_cast<void>(f_callingState);
    f_plane.m_flightTrack_p->setPoints(m_landingPath);
    f_plane.m_flightTrack_p->setVisible(false);
}

PlaneStateTaxiingToGate::PlaneStateTaxiingToGate(PlaneState* f_next)
    : PlaneState(f_next)
    , m_parkingHasStarted(false)
    , m_switchToNextState(false)
{}

void PlaneStateTaxiingToGate::updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane)
{
    auto adaptedSpeed = core::engine::adaptToFps(f_context, f_plane.m_speed);
    auto point_p = f_plane.m_flightTrack_p->moveToNextPoint(adaptedSpeed);

    if(point_p)
    {
        auto centrifiedPoint = f_plane.centrifyPoint(*point_p);
        f_plane.m_planeTexture_p->setPosition(centrifiedPoint.x, centrifiedPoint.y);
    }

    // Check wether plane has reached parking spot
    if(m_parkingHasStarted && f_plane.m_flightTrack_p->getRemainingLength() == 0.f)
    {
        m_switchToNextState = true;
    }
}

void PlaneStateTaxiingToGate::updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane)
{
    auto targetAngle = f_plane.calcTargetRotation();

    if(!std::isnan(targetAngle))
    {
        targetAngle = f_plane.rotateSmooth(targetAngle, f_context);
        f_plane.m_planeTexture_p->setRotation(targetAngle);
    }
}

void PlaneStateTaxiingToGate::updateSize(Plane& f_plane) {}

PlaneState* PlaneStateTaxiingToGate::checkForNextState(Plane& f_plane)
{
    if(m_switchToNextState)
    {
        m_next->onStateChange(*this, f_plane);
        return this->m_next;
    }

    return this;
}

void PlaneStateTaxiingToGate::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane)
{
    // Parking slot needs verification if plane selected
    if(!f_plane.m_verifyParkingSlot)
    {
        f_plane.m_verifyParkingSlot = f_plane.mouseHit(f_eventArgs);
    }
}

void PlaneStateTaxiingToGate::onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) {}

void PlaneStateTaxiingToGate::startParking(const std::vector<core::graphics::Vector>& f_path, Plane& f_plane)
{
    if(!m_parkingHasStarted) // Prevents that parking ist started multiple times
    {
        m_parkingHasStarted = true;
        f_plane.getFlightTrack()->setPoints(f_path);
    }
}

PlaneStateTaxiingToStart::PlaneStateTaxiingToStart(PlaneState* f_next)
    : PlaneState(f_next)
{}

void PlaneStateTaxiingToStart::updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane) 
{
    int debug = 0;
}
void PlaneStateTaxiingToStart::updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane) {}
void PlaneStateTaxiingToStart::updateSize(Plane& f_plane) {}

PlaneState* PlaneStateTaxiingToStart::checkForNextState(Plane& f_plane) 
{
    return this;
}

void PlaneStateTaxiingToStart::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) 
{
    if(!f_plane.m_verifyStartSlot)
    {
        f_plane.m_verifyStartSlot = f_plane.mouseHit(f_eventArgs);
    }
}

void PlaneStateTaxiingToStart::onMouseUp(const core::ui::MouseEventArgs& f_eventArgs, Plane& f_plane) {}

} // namespace elements
} // namespace game
