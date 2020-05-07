#ifndef GAME_ELEMENTS_PLANE_HPP_INLUDED
#define GAME_ELEMENTS_PLANE_HPP_INLUDED

#include "core/engine/game_element.hpp"

namespace game
{
namespace elements
{

class Plane : public core::engine::IGameElement
{
public:
    Plane();
    ~Plane();

    /// @brief
    virtual void load() override;

    /// @brief
    virtual void update() override;

    /// @brief
    virtual void draw() override;

    /// @brief
    virtual void onMouseButtonClicked(const core::ui::MousePressedEventArgs& f_eventArgs) override;

private:
};

} // namespace elements
} // namespace game

#endif