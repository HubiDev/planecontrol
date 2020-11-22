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

#ifndef GAME_ELEMENTS_RUWAY_HPP_INCLUDED
#define GAME_ELEMENTS_RUWAY_HPP_INCLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/rectangle.hpp"

#include <vector>

using core::graphics::Vector;

namespace game
{
namespace elements
{
class Runway : public core::engine::IGameElement
{
public:
    Runway();
    ~Runway();

    void load() override;

    void update(const core::engine::UpdateContext& f_context) override;

    void draw() override;

    bool isPointForLanding(const Vector& f_point);

    void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs) override;
    void onMouseUp(const core::ui::MouseEventArgs& f_eventArgs) override;

private:
    std::unique_ptr<core::graphics::Rectangle> m_texture_p;
    std::unique_ptr<core::graphics::Rectangle> m_landingRect_p;
    std::vector<Vector> m_landingPath;
    bool m_landingRectVisible;
};

} // namespace elements
} // namespace game

#endif