// ------------------------------------------------------------------------
// This file is part of planecontrol.

// planecontrol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// planecontrol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with planecontrol.  If not, see <http://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------

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
        current->load();
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

void GameBase::addGameElement(std::shared_ptr<core::engine::IGameElement> f_gameElement_p)
{
    m_gameElements.push_back(f_gameElement_p);
    m_mouse_p->registerAwareElement(*f_gameElement_p);
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
        current->update(context);
    }

    update();
}

void GameBase::drawGameElements()
{
    glClearColor(1.f, 1.f, 1.f, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    for(auto& current : m_gameElements)
    {
        current->draw();
    }

    draw();

    SDL_GL_SwapWindow(&m_gameWindow_p->getSDLWindow());
}

void GameBase::updateFps(std::int64_t f_durationSinceLastUpdate)
{
    m_currentFps = 1.f / (f_durationSinceLastUpdate / 1000.f / 1000.f);
    //std::cout << "FPS: " << m_currentFps << std::endl;
}

GameBase::~GameBase() {}

} // namespace engine

} // namespace core