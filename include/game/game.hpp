#ifndef GAME_GAME_HPP_INCLUDED
#define GAME_GAME_HPP_INCLUDED

#include "core/engine/game_base.hpp"

namespace game
{
class Game : public core::engine::GameBase
{
public:
    Game();
    ~Game();

protected:
    void update() override;
    void draw() override;

private:
    /* data */
};

} // namespace game

#endif