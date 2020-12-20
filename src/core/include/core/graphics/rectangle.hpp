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

#ifndef CORE_GRAPHICS_HPP_INCLUDED
#define CORE_GRAPHICS_HPP_INCLUDED

#include "core/graphics/color.hpp"
#include "core/graphics/vector.hpp"

#include <array>
#include <tuple>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>

namespace core
{
namespace graphics
{

class Rectangle
{
public:
    Rectangle(std::tuple<float, float> f_position, std::tuple<float, float> f_size);
    ~Rectangle();

    void draw();
    void move(float f_offsetX, float f_offsetY);
    void setPosition(float f_posX, float f_posY);

    Vector getSize();
    Vector getPosition();
    void setColor(const ColorRgb& f_color);

private:
    void render();

    float m_posX;
    float m_posY;
    float m_width;
    float m_height;

    GLuint m_vboReference;
    std::array<float, 6U> m_vertexBuffer;
    core::graphics::ColorRgb m_color;
};

} // namespace graphics

} // namespace core

#endif