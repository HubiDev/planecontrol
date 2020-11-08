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

#ifndef CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED
#define CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED

#include "core/ui/drawable.hpp"
#include "core/ui/mouse_aware.hpp"

namespace core
{
namespace engine
{

// forward decalrations
class UpdateContext;

class IGameElement : public ui::IDrawable, public ui::IMouseAware
{
public:
    virtual ~IGameElement(){};

    IGameElement(const IGameElement&) = delete;
    IGameElement(IGameElement&&) = delete;
    IGameElement& operator=(const IGameElement&) = delete;
    IGameElement& operator=(IGameElement&&) = delete;

    /// @brief 
    virtual void load() = 0;

    /// @brief
    virtual void update(const UpdateContext& f_context) = 0;

protected:
    inline IGameElement()
        : ui::IDrawable()
        , ui::IMouseAware(){};
};

} // namespace engine
} // namespace core

#endif // CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED
