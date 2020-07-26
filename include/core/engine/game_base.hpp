#ifndef CORE_ENGINE_GAME_BASE_HPP_INCLUDED
#define CORE_ENGINE_GAME_BASE_HPP_INCLUDED

#include <vector>
#include <string>

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

protected:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void onAfterInitialize();

    void addGameElement(IGameElement& f_gameElement);

private:
    void updateGameElements();
    void drawGameElements();

    // CAUTION: Context shall always be the first object to be constructed
    // and the last one to be destructed
    std::unique_ptr<ui::SdlContext> m_sdlContext_p;
    std::unique_ptr<ui::EventManager> m_eventManager_p;
    std::unique_ptr<ui::Mouse> m_mouse_p;
    std::unique_ptr<ui::Window> m_gameWindow_p;
    std::vector<std::reference_wrapper<IGameElement>> m_gameElements;

    bool m_exitRequested;
    int64_t m_lastUpdateTimestamp;

    // TODO make setting dependend
    static constexpr int32_t k_windowWidth = 1280;
    static constexpr int32_t k_windowHeight = 720;
    const std::string m_windowTitle;
};

} // namespace engine

} // namespace core

#endif