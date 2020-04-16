#ifndef CORE_ENGINE_GAME_HPP_INCLUDED
#define CORE_ENGINE_GAME_HPP_INCLUDED

#include "core/ui/event_manager.hpp"
#include "core/ui/sdl_context.hpp"
#include "core/ui/window.hpp"

namespace core
{
namespace engine
{
class Game
{

public:
    Game();
    ~Game();

    void intialize();

    /// @brief This is "the" method that starts it all...
    void run();

private:

    void updateGameElements();
    void drawGameElements();

    // CAUTION: Context shall always be the first object to be constructed 
    // and the last one to be destructed
    ui::SdlContext m_sdlContext;

    ui::EventManager m_eventManager;
    std::unique_ptr<ui::Window> m_gameWindow_p;
    bool m_exitRequested;

    // TODO make setting dependend
    static constexpr int32_t k_windowWidth = 1280;
    static constexpr int32_t k_windowHeight = 720;
    const std::string m_windowTitle;
};

} // namespace engine

} // namespace core

#endif