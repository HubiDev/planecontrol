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