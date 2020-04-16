#ifndef CORE_UI_EVENT_MANAGER_HPP_INCLUDED
#define CORE_UI_EVENT_MANAGER_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <functional>
#include <unordered_map>

namespace core
{
namespace ui
{
class EventManager
{
public:
    EventManager();
    ~EventManager();

    /// @brief
    /// @param[in] f_eventId
    /// @param[in] f_eventCallback
    void addEventCallback(int32_t f_eventId, std::function<void(const SDL_Event&)> f_eventCallback);

    /// @brief Gets all events out of the queue and executes the registered callbacks
    void processEvents();

private:
    std::unordered_map<int32_t, std::function<void(const SDL_Event&)>> m_eventCallbacks;
};
} // namespace ui
} // namespace core

#endif