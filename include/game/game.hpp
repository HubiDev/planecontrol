#ifndef GAME_GAME_HPP_INCLUDED
#define GAME_GAME_HPP_INCLUDED

#include "core/engine/game_base.hpp"
#include "game/elements/flight_track.hpp"

namespace game
{
class Game : public core::engine::GameBase
{
public:
    Game();
    ~Game();

protected:
    void onAfterInitialize() override;
    void update() override;
    void draw() override;

private:

    elements::FlightTrack m_flightTrack;
    
};

} // namespace game

#endif