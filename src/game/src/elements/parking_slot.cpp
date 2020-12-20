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

#include "game/elements/parking_slot.hpp"

namespace game
{
namespace elements
{

ParkingSlot::ParkingSlot(const std::vector<core::graphics::Vector>& f_pathToSlot,
                         const std::vector<core::graphics::Vector>& f_pathToStart)
    : m_isUsed(false)
    , m_isVisble(false)
    , m_pathToSlot(f_pathToSlot)
    , m_pathToStart(f_pathToStart)
    , m_slotRect_p()
{}

ParkingSlot::~ParkingSlot() {}

void ParkingSlot::load() {}
void ParkingSlot::update(const core::engine::UpdateContext& f_context) {}

void ParkingSlot::draw()
{
    if(m_isVisble)
    {
        m_slotRect_p->draw();
    }
}

} // namespace elements
} // namespace game
