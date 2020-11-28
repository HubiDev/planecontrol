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
    , m_flightTrackComplete(false)
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
    if(f_plane.m_flightTrack_p->getRemainingLength() == 0.f && m_flightTrackComplete)
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
    bool planeWasHit = core::graphics::geometry::isContainedInRegion(
        f_plane.m_planeTexture_p->getPosition(),
        f_plane.m_planeTexture_p->getSize(),
        {static_cast<float>(f_eventArgs.m_posX), static_cast<float>(f_eventArgs.m_posY)});

    if(planeWasHit)
    {
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
    if(f_plane.m_landingPointFunc)
    {
        bool runwayWasHit = f_plane.m_landingPointFunc(
            {static_cast<float>(f_eventArgs.m_posX), static_cast<float>(f_eventArgs.m_posY)});

        if(!runwayWasHit)
        {
            f_plane.m_flightTrack_p->clear();
            m_flightTrackComplete = false;
        }
        else
        {
            m_flightTrackComplete = true;
        }

        f_plane.m_flightTrack_p->setActive(false);
    }
    else
    {
        throw new std::runtime_error("Plane was not initialzed correctly");
    }
}

PlaneState* PlaneStateFlying::checkForNextState()
{
    if(m_switchToNextState)
    {
        return this->m_next;
    }

    return this;
}

PlaneStateLanding::PlaneStateLanding(PlaneState* f_next)
    : PlaneState(f_next)
    , m_landingPath()
    , m_landingAnimation{0.f, 150.f, 30.f}
{}

void PlaneStateLanding::updatePosition(const core::engine::UpdateContext& f_context, Plane& f_plane) {}
void PlaneStateLanding::updateRotation(const core::engine::UpdateContext& f_context, Plane& f_plane) {}

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

PlaneState* PlaneStateLanding::checkForNextState()
{
    return this;
}

} // namespace elements
} // namespace game
