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

#ifndef CORE_UI_MOUSE_EVENT_ARGS_HPP_INCLUDED
#define CORE_UI_MOUSE_EVENT_ARGS_HPP_INCLUDED

#include <stdint.h>

namespace core
{
namespace ui
{

enum class MouseButton
{
    left,
    right,
    middle
};

struct MouseEventArgs
{
    int32_t m_posX;
    int32_t m_posY;
    MouseButton m_button;
};

} // namespace ui
} // namespace core

#endif