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

#include <iostream>

namespace game
{
namespace elements
{
Runway::Runway()
    : core::engine::IGameElement()
    , m_landingRect_p()
    , m_texture_p()
    , m_parkingSlots()
    , m_landingRectVisible(false)
    , m_landingPath{{870.f, 75.f}, {870.f, 650.f}}
    , m_location()
    , m_size()
    , m_texturePath()
    , m_lastSelectedSlot_p(nullptr)
{}

Runway::~Runway() {}

void Runway::setLocation(const core::graphics::Vector& f_location)
{
    m_location = f_location;
}

void Runway::setSize(const core::graphics::Vector& f_size)
{
    m_size = f_size;
}

void Runway::setTexturePath(const std::string& f_texturePath)
{
    m_texturePath = f_texturePath;
}

void Runway::setLandingPath(const std::vector<Vector>& f_landingPath)
{
    m_landingPath = f_landingPath;
}

void Runway::setParkingSlots(const std::vector<std::shared_ptr<ParkingSlot>>& f_parkingSlots)
{
    m_parkingSlots = f_parkingSlots;
}

void Runway::load()
{
    m_texture_p =
        std::unique_ptr<core::graphics::Texture>(new core::graphics::Texture(m_texturePath, m_location, m_size));
    m_texture_p->load();

    auto& landingLocation = m_landingPath[0];

    m_landingRect_p = std::unique_ptr<core::graphics::Rectangle>(
        new core::graphics::Rectangle({landingLocation.x - 5.f, landingLocation.y - 5.f}, {10.f, 10.f}));

    m_landingRect_p->setColor({0.1f, 0.1f, 0.1f});

    for(auto& currentSlot : m_parkingSlots)
    {
        currentSlot->load();
    }
}

void Runway::update(const core::engine::UpdateContext& f_context) {}

void Runway::draw()
{
    m_texture_p->draw();

    if(m_landingRectVisible)
    {
        m_landingRect_p->draw();
    }

    for(auto& currentSlot : m_parkingSlots)
    {
        currentSlot->draw();
    }
}

bool Runway::isPointForLanding(const Vector& f_point)
{
    return core::graphics::geometry::isContainedInRegion(
        m_landingRect_p->getPosition(), m_landingRect_p->getSize(), f_point);
}

void Runway::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs)
{
    m_landingRectVisible = true;
    m_lastSelectedSlot_p = nullptr;

    for(auto& slot : m_parkingSlots)
    {
        if(slot->mouseHit(f_eventArgs))
        {
            m_lastSelectedSlot_p = slot;
        }
    }
}

void Runway::onMouseUp(const core::ui::MouseEventArgs& f_eventArgs)
{
    m_landingRectVisible = false;
}

const std::vector<Vector>& Runway::getLandingPath()
{
    return m_landingPath;
}

std::shared_ptr<ParkingSlot> Runway::getLastSelectedParkingSlot()
{
    return m_lastSelectedSlot_p;
}

} // namespace elements
} // namespace game
