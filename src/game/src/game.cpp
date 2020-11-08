#include "game/game.hpp"

namespace game
{
Game::Game()
    : core::engine::GameBase()
    , m_planeFactory()
{}

Game::~Game() {}

void Game::onAfterInitialize()
{
    auto& plane = m_planeFactory.createPlane();
    addGameElement(plane.getFlightTrack());
    addGameElement(plane);
}

void Game::update() {}

void Game::draw() {}

} // namespace game