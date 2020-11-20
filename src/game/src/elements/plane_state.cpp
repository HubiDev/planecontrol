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
#include "game/elements/plane.hpp"

#include <cmath>

namespace game
{
namespace elements
{

PlaneStateFlying::PlaneStateFlying()
    : PlaneState()
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

void PlaneStateFlying::updateSize(Plane& f_plane)
{
    if(f_plane.m_landingAnimation.isActive(f_plane.m_flightTrack_p->getRemainingLength()) &&
       f_plane.m_flightTrackComplete)
    {
        auto sizeDiff = f_plane.m_landingAnimation.update(f_plane.m_flightTrack_p->getRemainingLength());
        auto planeSize = f_plane.m_planeTexture_p->getSize();
        f_plane.m_planeTexture_p->setSize({planeSize.x - sizeDiff, planeSize.y - sizeDiff});
    }
}

} // namespace elements
} // namespace game
