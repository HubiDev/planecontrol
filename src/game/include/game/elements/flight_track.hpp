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

#ifndef GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
#define GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/polyline.hpp"
#include <memory>

namespace game
{
namespace elements
{
class FlightTrack : public core::engine::IGameElement
{

public:
    FlightTrack();
    ~FlightTrack();

    void load() override;
    void draw() override;
    void update(const core::engine::UpdateContext& f_context) override;

    void setActive(bool f_isActive);
    bool isActive();

    void clear();

    const core::graphics::Vector* moveToNextPoint(float f_distance);
    const core::graphics::Vector* getPoint(int32_t f_index);
    core::graphics::Vector getDirection();

    void onMouseButtonPressed(const core::ui::MouseEventArgs& f_eventArgs) override;

    float calcDistanceToNextPoint() const;

    void shiftStart(float f_distanceToShift, float f_distanceToNext);

    float getRemainingLength();

private:
    std::unique_ptr<core::graphics::Polyline> m_line_p;
    bool m_isActive;
    static constexpr float TRACK_THICKNESS = 1.5f;
};

} // namespace elements
} // namespace game

#endif // GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
