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

namespace game
{
namespace elements
{
PlaneStateFlying::PlaneStateFlying()
    : PlaneState()
{}

void PlaneStateFlying::updatePosition(const core::engine::UpdateContext& f_context) {}
void PlaneStateFlying::updateRotation(const core::engine::UpdateContext& f_context) {}
void PlaneStateFlying::updateSize() {}


} // namespace elements
} // namespace game
