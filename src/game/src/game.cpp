#include "game/game.hpp"

namespace game
{
Game::Game()
    : core::engine::GameBase()
    , m_planeFactory()
    , m_runway_p()
{}

Game::~Game() {}

void Game::onAfterInitialize()
{
    m_runway_p = std::unique_ptr<elements::Runway>(new elements::Runway());
    addGameElement(*m_runway_p);

    auto& plane = m_planeFactory.createPlane();
    addGameElement(plane.getFlightTrack());
    addGameElement(plane);
}

void Game::update() {}

void Game::draw() {}

} // namespace game