#include "core/engine/game_base.hpp"
#include <SDL2/SDL_opengl.h>

namespace core
{
namespace engine
{
GameBase::GameBase()
    : m_sdlContext()
    , m_eventManager()
    , m_mouse()
    , m_gameWindow_p(nullptr)
    , m_gameElements()
    , m_exitRequested(false)
    , m_windowTitle("Plane Control")
{}

void GameBase::initialize()
{
    m_eventManager.addEventCallback(SDL_QUIT, [this](const SDL_Event& f_event) -> void { m_exitRequested = true; });

    m_eventManager.addEventCallback(SDL_MOUSEBUTTONDOWN, [this](const SDL_Event& f_event) -> void {
        m_mouse.mouseButtonDownCallback(f_event.button);
    });

    m_eventManager.addEventCallback(
        SDL_MOUSEBUTTONUP, [this](const SDL_Event& f_event) -> void { m_mouse.mouseButtonUpCallback(f_event.button); });

    m_eventManager.addEventCallback(
        SDL_MOUSEMOTION, [this](const SDL_Event& f_event) -> void { m_mouse.mouseMoveCallback(f_event.motion); });

    m_gameWindow_p = std::unique_ptr<ui::Window>(new ui::Window(m_windowTitle, k_windowWidth, k_windowHeight));
    m_gameWindow_p->initialize();

    // in this call all game elements shall be added by the subclass
    onAfterInitialize();
}

void GameBase::loadContent()
{
    // load game elements after window was created
    for(auto& current : m_gameElements)
    {
        current.get().load();
    }
}

void GameBase::onAfterInitialize() {}

void GameBase::run()
{
    // This loop is never left until the user want to quit the game
    while(!m_exitRequested)
    {
        m_eventManager.processEvents();
        m_mouse.update();
        updateGameElements();
        drawGameElements();
    }

    m_gameWindow_p.reset(); // close the window
}

void GameBase::addGameElement(core::engine::IGameElement& f_gameElement)
{
    m_gameElements.push_back(std::reference_wrapper<IGameElement>(f_gameElement));
    m_mouse.registerAwareElement(f_gameElement);
}

void GameBase::updateGameElements()
{
    //TODO fill context
    UpdateContext context{};

    for(auto& current : m_gameElements)
    {
        current.get().update(context);
    }

    update();
}

void GameBase::drawGameElements()
{
    glClearColor(1.f, 1.f, 1.f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto& current : m_gameElements)
    {
        current.get().draw();
    }

    draw();

    SDL_GL_SwapWindow(&m_gameWindow_p->getSDLWindow());
}

GameBase::~GameBase() {}

} // namespace engine

} // namespace core