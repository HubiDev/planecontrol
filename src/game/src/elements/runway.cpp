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

#include "game/elements/runway.hpp"
#include "core/graphics/geometry.hpp"

namespace game
{
namespace elements
{
Runway::Runway()
    : core::engine::IGameElement()
    , m_texture_p()
    , m_landingRect_p()
{}

Runway::~Runway() {}

void Runway::load()
{
    m_texture_p =
        std::unique_ptr<core::graphics::Rectangle>(new core::graphics::Rectangle({900.f, 400.f}, {20.f, 100.f}));
    m_landingRect_p =
        std::unique_ptr<core::graphics::Rectangle>(new core::graphics::Rectangle({900.f, 350.f}, {10.f, 10.f}));
}

void Runway::update(const core::engine::UpdateContext& f_context) {}

void Runway::draw()
{
    m_texture_p->draw();
    m_landingRect_p->draw();
}

bool Runway::isPointForLanding(const Vector& f_point)
{
    return core::graphics::geometry::isContainedInRegion(
        m_landingRect_p->getPosition(), m_landingRect_p->getSize(), f_point);
}

} // namespace elements
} // namespace game
