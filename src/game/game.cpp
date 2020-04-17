#include "game/game.hpp"

namespace game
{
Game::Game()
    : core::engine::GameBase()
    , m_flightTrack()
{}

Game::~Game() {}

void Game::onAfterInitialize()
{
    addGameElement(m_flightTrack);
}

void Game::update() {}

void Game::draw() {}

} // namespace game