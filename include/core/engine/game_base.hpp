#ifndef CORE_ENGINE_GAME_BASE_HPP_INCLUDED
#define CORE_ENGINE_GAME_BASE_HPP_INCLUDED

#include "core/ui/event_manager.hpp"
#include "core/ui/mouse.hpp"
#include "core/ui/sdl_context.hpp"
#include "core/ui/window.hpp"

#include "core/engine/game_element.hpp"

#include <vector>

namespace core
{
namespace engine
{
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

protected:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void onAfterInitialize();

    void addGameElement(core::engine::IGameElement& f_gameElement);

private:
    void updateGameElements();
    void drawGameElements();

    // CAUTION: Context shall always be the first object to be constructed
    // and the last one to be destructed
    ui::SdlContext m_sdlContext;

    ui::EventManager m_eventManager;
    ui::Mouse m_mouse;

    std::unique_ptr<ui::Window> m_gameWindow_p;

    std::vector<std::reference_wrapper<IGameElement>> m_gameElements;

    bool m_exitRequested;

    // TODO make setting dependend
    static constexpr int32_t k_windowWidth = 1280;
    static constexpr int32_t k_windowHeight = 720;
    const std::string m_windowTitle;
};

} // namespace engine

} // namespace core

#endif