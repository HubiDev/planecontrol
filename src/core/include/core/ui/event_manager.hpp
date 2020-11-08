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

#ifndef CORE_UI_EVENT_MANAGER_HPP_INCLUDED
#define CORE_UI_EVENT_MANAGER_HPP_INCLUDED

#include <functional>
#include <unordered_map>

// forward declarations
union SDL_Event;

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
    void processEvents() const;

private:
    std::unordered_map<int32_t, std::function<void(const SDL_Event&)>> m_eventCallbacks;
};
} // namespace ui
} // namespace core

#endif