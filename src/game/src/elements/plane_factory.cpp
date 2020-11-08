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

#include "game/elements/plane_factory.hpp"

namespace game
{
namespace elements
{

PlaneFactory::PlaneFactory()
    : m_planes()
    , m_flightTracks()
{}

PlaneFactory::~PlaneFactory() {}

Plane& PlaneFactory::createPlane()
{
    auto flightTrack_p = std::shared_ptr<FlightTrack>(new FlightTrack());
    auto plane_p = std::shared_ptr<Plane>(new Plane(flightTrack_p));
    m_flightTracks.push_back(flightTrack_p);
    m_planes.push_back(plane_p);
    return *plane_p;
}

} // namespace elements

} // namespace game