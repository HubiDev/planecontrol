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

#ifndef CORE_GRAPHICS_ANIMATION_HPP_INCLUDED
#define CORE_GRAPHICS_ANIMATION_HPP_INCLUDED

#include "core/engine/update_context.hpp"

namespace core
{
namespace graphics
{
class Animation
{
public:
    Animation(float f_refStart, float f_refEnd, float f_animationVal);
    float update(float f_currentRef);
    bool isActive(float f_currentRef);

private:
    const float m_refStart;
    const float m_refEnd;
    const float m_diff;
    const float m_animationVal;
    float m_lastVal;
};

} // namespace graphics
} // namespace core

#endif