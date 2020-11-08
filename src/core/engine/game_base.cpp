#include <SDL2/SDL_opengl.h>
#include <chrono>

#include "core/engine/game_base.hpp"
#include "core/engine/game_element.hpp"
#include "core/engine/update_context.hpp"
#include "core/ui/event_manager.hpp"
#include "core/ui/mouse.hpp"
#include "core/ui/sdl_context.hpp"
#include "core/ui/window.hpp"

#include <iostream>

namespace core
{
namespace engine
{
GameBase::GameBase()
    : m_sdlContext_p{new ui::SdlContext()}
    , m_eventManager_p{new ui::EventManager()}
    , m_mouse_p{new ui::Mouse()}
    , m_gameWindow_p{nullptr}
    , m_gameElements{}
    , m_lastUpdateTimestamp{}
    , m_exitRequested{false}
    , m_windowTitle{"Plane Control"}
{}

void GameBase::initialize()
{
    m_eventManager_p->addEventCallback(SDL_QUIT, [this](const SDL_Event& f_event) -> void { m_exitRequested = true; });

    m_eventManager_p->addEventCallback(SDL_MOUSEBUTTONDOWN, [this](const SDL_Event& f_event) -> void {
        m_mouse_p->mouseButtonDownCallback(f_event.button);
    });

    m_eventManager_p->addEventCallback(SDL_MOUSEBUTTONUP, [this](const SDL_Event& f_event) -> void {
        m_mouse_p->mouseButtonUpCallback(f_event.button);
    });

    m_eventManager_p->addEventCallback(
        SDL_MOUSEMOTION, [this](const SDL_Event& f_event) -> void { m_mouse_p->mouseMoveCallback(f_event.motion); });

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
        m_eventManager_p->processEvents();
        m_mouse_p->update();
        updateGameElements();
        drawGameElements();
    }

    m_gameWindow_p.reset(); // close the window
}

float GameBase::getCurrentFps()
{
    return m_currentFps;
}

void GameBase::addGameElement(core::engine::IGameElement& f_gameElement)
{
    m_gameElements.push_back(std::reference_wrapper<IGameElement>(f_gameElement));
    m_mouse_p->registerAwareElement(f_gameElement);
}

void GameBase::updateGameElements()
{
    UpdateContext context{};
    auto now =
        std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch())
            .count();

    context.m_durationSinceLastUpdate = {now - m_lastUpdateTimestamp};
    m_lastUpdateTimestamp = now;
    updateFps(context.m_durationSinceLastUpdate);

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

void GameBase::updateFps(std::int64_t f_durationSinceLastUpdate)
{
    m_currentFps = 1.f / (f_durationSinceLastUpdate / 1000.f / 1000.f);
    std::cout << "FPS: " << m_currentFps << std::endl;
}

GameBase::~GameBase() {}

} // namespace engine

} // namespace core