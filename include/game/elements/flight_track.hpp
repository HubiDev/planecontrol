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

    void onMouseButtonPressed(const core::ui::MouseEventArgs& f_eventArgs) override;

    float calcDistanceToNextPoint() const;

    void shiftStart(float f_distanceToShift, float f_distanceToNext);

private:
    std::unique_ptr<core::graphics::Polyline> m_line_p;
    bool m_isActive;
    static constexpr float TRACK_THICKNESS = 2.5f;
};

} // namespace elements
} // namespace game

#endif // GAME_ELEMENTS_FLIGHT_TRACK_HPP_INCLUDED
