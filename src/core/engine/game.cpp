#include "core/engine/game.hpp"

namespace core
{
namespace engine
{
Game::Game()
    : m_sdlContext()
    , m_eventManager()
    , m_gameWindow_p(nullptr)
    , m_exitRequested(false)
    , m_windowTitle("Plane Control")
{}

void Game::intialize()
{
    m_eventManager.addEventCallback(SDL_QUIT, [this](const SDL_Event& f_event) -> void { m_exitRequested = true; });
    m_gameWindow_p = std::unique_ptr<ui::Window>(new ui::Window(m_windowTitle, k_windowWidth, k_windowHeight));
    m_gameWindow_p->initialize();
}

void Game::run()
{
    // This loop is never left until the user want to quit the game
    while(!m_exitRequested)
    {
        m_eventManager.processEvents();
        updateGameElements();
        drawGameElements();
    }

    m_gameWindow_p.reset(); // close the window
}

void Game::updateGameElements() 
{
    // TODO
}

void Game::drawGameElements() 
{
    m_gameWindow_p->getRenderer().prepareRendering();
    m_gameWindow_p->getRenderer().finishRendering();
}

Game::~Game() {}

} // namespace engine

} // namespace core