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
#include "core/graphics/geometry.hpp"
#include "core/ui/mouse_event_args.hpp"

namespace game
{
namespace elements
{

ParkingSlot::ParkingSlot(const std::vector<core::graphics::Vector>& f_pathToSlot,
                         const std::vector<core::graphics::Vector>& f_pathToStart)
    : m_isUsed(false)
    , m_isVisble(true)
    , m_pathToSlot(f_pathToSlot)
    , m_pathToStart(f_pathToStart)
    , m_slotRect_p()
{}

ParkingSlot::~ParkingSlot() {}

void ParkingSlot::load()
{
    auto& endPoint = m_pathToSlot.back();
    m_slotRect_p = std::unique_ptr<core::graphics::Rectangle>(
        new core::graphics::Rectangle({endPoint.x, endPoint.y}, {10.f, 10.f}));
}

void ParkingSlot::update(const core::engine::UpdateContext& f_context) {}

void ParkingSlot::draw()
{
    if(m_isVisble)
    {
        m_slotRect_p->draw();
    }
}

bool ParkingSlot::mouseHit(const core::ui::MouseEventArgs& f_eventArgs)
{
    return core::graphics::geometry::isContainedInRegion(
        m_slotRect_p->getPosition(),
        m_slotRect_p->getSize(),
        {static_cast<float>(f_eventArgs.m_posX), static_cast<float>(f_eventArgs.m_posY)});
}

const std::vector<core::graphics::Vector>& ParkingSlot::getPathToSlot() const
{
    return m_pathToSlot;
}

} // namespace elements
} // namespace game
