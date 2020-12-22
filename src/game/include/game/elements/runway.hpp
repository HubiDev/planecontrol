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
#include "core/graphics/texture.hpp"
#include "core/graphics/circle.hpp"
#include "game/elements/parking_slot.hpp"
#include "game/elements/plane.hpp"

#include <map>
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

    void setLocation(const core::graphics::Vector& f_location);
    void setSize(const core::graphics::Vector& f_size);
    void setTexturePath(const std::string& f_texturePath);
    void setLandingPath(const std::vector<Vector>& f_landingPath);
    void setTakeoffPath(const std::vector<Vector>& f_takeoffPath);
    void setParkingSlots(const std::vector<std::shared_ptr<ParkingSlot>>& f_parkingSlots);

    void load() override;
    void update(const core::engine::UpdateContext& f_context) override;
    void draw() override;

    bool isPointForLanding(const Vector& f_point);

    void onMouseDown(const core::ui::MouseEventArgs& f_eventArgs) override;
    void onMouseUp(const core::ui::MouseEventArgs& f_eventArgs) override;

    const std::vector<Vector>& getLandingPath();
    const std::vector<Vector>& getTakeoffPath();

    std::shared_ptr<ParkingSlot> getLastSelectedParkingSlot();

    bool takeoffWasSelected();

    void registerParking(std::shared_ptr<ParkingSlot> f_slot_p, std::shared_ptr<Plane> f_plane_p);
    std::shared_ptr<ParkingSlot> unregisterParking(std::shared_ptr<Plane> f_plane_p);

private:
    std::unique_ptr<core::graphics::Rectangle> m_landingRect_p;
    std::unique_ptr<core::graphics::Texture> m_texture_p;
    std::unique_ptr<core::graphics::Rectangle> m_takeoffRect_p;

    std::unique_ptr<core::graphics::Circle> m_circle_p;

    std::vector<std::shared_ptr<ParkingSlot>> m_parkingSlots;
    std::map<std::shared_ptr<Plane>, std::shared_ptr<ParkingSlot>> m_parkingRegistry;

    std::vector<Vector> m_landingPath;
    std::vector<Vector> m_takeoffPath;

    core::graphics::Vector m_location;
    core::graphics::Vector m_size;
    std::string m_texturePath;

    bool m_landingRectVisible;
    std::shared_ptr<ParkingSlot> m_lastSelectedSlot_p;

    bool m_takeoffWasSelected;
};

} // namespace elements
} // namespace game

#endif