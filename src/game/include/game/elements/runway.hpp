#ifndef GAME_ELEMENTS_RUWAY_HPP_INCLUDED
#define GAME_ELEMENTS_RUWAY_HPP_INCLUDED

#include "core/engine/game_element.hpp"
#include "core/graphics/rectangle.hpp"

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

private:
    std::unique_ptr<core::graphics::Rectangle> m_texture_p;
};

} // namespace elements
} // namespace game

#endif