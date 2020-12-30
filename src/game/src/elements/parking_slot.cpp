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
    , m_pathToSlot(f_pathToSlot)
    , m_pathToStart(f_pathToStart)
    , m_slotPoint_p()
{}

ParkingSlot::~ParkingSlot() {}

void ParkingSlot::load()
{
    auto& endPoint = m_pathToSlot.back();
    m_slotPoint_p = std::unique_ptr<core::graphics::Circle>(new core::graphics::Circle({endPoint.x, endPoint.y}, 10.f));
    m_slotPoint_p->setColor({0.f, 0.f, 1.f, 1.f});
}

void ParkingSlot::update(const core::engine::UpdateContext& f_context) {}

void ParkingSlot::draw()
{
    if(!m_isUsed)
    {
        m_slotPoint_p->draw();
    }
}

bool ParkingSlot::mouseHit(const core::ui::MouseEventArgs& f_eventArgs)
{
    return core::graphics::geometry::isContainedInRegion(
        m_slotPoint_p->getPosition(),
        m_slotPoint_p->getRadius(),
        {static_cast<float>(f_eventArgs.m_posX), static_cast<float>(f_eventArgs.m_posY)});
}

const std::vector<core::graphics::Vector>& ParkingSlot::getPathToSlot() const
{
    return m_pathToSlot;
}

const std::vector<core::graphics::Vector>& ParkingSlot::getPathToTakeoff() const
{
    return m_pathToStart;
}

void ParkingSlot::setUsed(bool f_used)
{
    m_isUsed = f_used;
}

} // namespace elements
} // namespace game
