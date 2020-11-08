#ifndef GAME_ELEMENTS_RUWAY_HPP_INCLUDED
#define GAME_ELEMENTS_RUWAY_HPP_INCLUDED

#include "core/engine/game_element.hpp"

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
};

} // namespace elements
} // namespace game

#endif