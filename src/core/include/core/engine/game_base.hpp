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

#ifndef CORE_ENGINE_GAME_BASE_HPP_INCLUDED
#define CORE_ENGINE_GAME_BASE_HPP_INCLUDED

#include <vector>
#include <string>
#include <memory>

namespace core
{
// forward declarations
namespace ui
{
class Window;
class SdlContext;
class EventManager;
class Mouse;
}

namespace engine
{
// forward declarations
class IGameElement;

class GameBase
{

public:
    GameBase();
    virtual ~GameBase();

    /// @brief Lightweight init of the game
    void initialize();

    /// @brief Loads all content (allocates buffer, loads textures etc.)
    /// @details Can be done during startup screen is shown
    void loadContent();

    /// @brief This is "the" method that starts it all...
    void run();

    float getCurrentFps();

protected:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void onAfterInitialize();

    void addGameElement(IGameElement& f_gameElement);

private:
    void updateGameElements();
    void drawGameElements();
    void updateFps(std::int64_t f_durationSinceLastUpdate);

    // CAUTION: Context shall always be the first object to be constructed
    // and the last one to be destructed
    std::unique_ptr<ui::SdlContext> m_sdlContext_p;
    std::unique_ptr<ui::EventManager> m_eventManager_p;
    std::unique_ptr<ui::Mouse> m_mouse_p;
    std::unique_ptr<ui::Window> m_gameWindow_p;
    std::vector<std::reference_wrapper<IGameElement>> m_gameElements;

    bool m_exitRequested;
    std::int64_t m_lastUpdateTimestamp;
    float m_currentFps;

    // TODO make setting dependend
    static constexpr int32_t k_windowWidth = 1280;
    static constexpr int32_t k_windowHeight = 720;
    const std::string m_windowTitle;
};

} // namespace engine

} // namespace core

#endif