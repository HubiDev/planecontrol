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

#ifndef GAME_ELEMENTS_PLANE_FACTORY_HPP_INCLUDED
#define GAME_ELEMENTS_PLANE_FACTORY_HPP_INCLUDED

#include "game/elements/flight_track.hpp"
#include "game/elements/plane.hpp"
#include <memory>
#include <vector>

namespace game
{
namespace elements
{
class PlaneFactory
{
public:
    PlaneFactory();
    ~PlaneFactory();

    std::shared_ptr<Plane> createPlane();
    const std::vector<std::shared_ptr<Plane>>& getCreatedPlanes();

private:
    std::vector<std::shared_ptr<Plane>> m_planes;
    std::vector<std::shared_ptr<FlightTrack>> m_flightTracks;
};

} // namespace elements

} // namespace game

#endif // GAME_ELEMENTS_PLANE_FACTORY_HPP_INCLUDED
