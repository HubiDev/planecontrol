#include "core/ui/event_manager.hpp"
#include <iostream>
#include <SDL2/SDL_events.h>

namespace core
{
namespace ui
{
EventManager::EventManager()
    : m_eventCallbacks()
{}

EventManager::~EventManager() {}

/// @brief
/// @param[in] f_eventId
/// @param[in] f_eventCallback
void EventManager::addEventCallback(int32_t f_eventId, std::function<void(const SDL_Event&)> f_eventCallback)
{
    auto result = m_eventCallbacks.insert({f_eventId, f_eventCallback});

    if(!result.second)
    {
        throw std::runtime_error("Failed to register event callback");
    }
}

/// @brief Gets all events out of the queue and executes the registered callbacks
void EventManager::processEvents() const
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        auto searchResult_p = m_eventCallbacks.find(event.type);
        if(m_eventCallbacks.end() != searchResult_p)
        {
            searchResult_p->second(event);
        }
    }
}

} // namespace ui

} // namespace core