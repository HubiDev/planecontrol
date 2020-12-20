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

#ifndef GAME_ELEMENTS_PARKING_SLOT_HPP_INCLUDED
#define GAME_ELEMENTS_PARKING_SLOT_HPP_INCLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/rectangle.hpp"
#include "core/graphics/vector.hpp"

#include <memory>
#include <vector>

namespace game
{
namespace elements
{

class ParkingSlot : public core::engine::IGameElement
{
public:
    ParkingSlot(const std::vector<core::graphics::Vector>& f_pathToSlot,
                const std::vector<core::graphics::Vector>& f_pathToStart);

    ParkingSlot() = default;
    ~ParkingSlot();

    void load() final;
    void update(const core::engine::UpdateContext& f_context) final;
    void draw() final;

    bool mouseHit(const core::ui::MouseEventArgs& f_eventArgs);

private:
    bool m_isUsed;
    bool m_isVisble;

    std::vector<core::graphics::Vector> m_pathToSlot;
    std::vector<core::graphics::Vector> m_pathToStart;
    std::unique_ptr<core::graphics::Rectangle> m_slotRect_p;
};

} // namespace elements
} // namespace game

#endif