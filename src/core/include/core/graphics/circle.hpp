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

#ifndef CORE_GRAPHICS_CIRCLE_HPP_INCLUDED
#define CORE_GRAPHICS_CIRCLE_HPP_INCLUDED

#include "core/graphics/color.hpp"
#include "vector.hpp"

#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>

#include <vector>
#include <cmath>

namespace core
{
namespace graphics
{
class Circle
{
public:
    Circle(const Vector& f_position, float f_radius);
    void draw();
    void setColor(const ColorRgba& f_color);

    const Vector& getPosition();
    float getRadius();    

private:
    void render();
    void renderColor();
    void addColor(const ColorRgba& f_color);

    Vector m_position;
    float m_radius;
    float m_colorGradient;
    std::vector<float> m_vertexBuffer;
    std::vector<float> m_colorBuffer;

    static constexpr float k_res = 200.f;
    static constexpr float k_angleLimit = (2.f * M_PI);
    static constexpr float k_segmentSize = (k_angleLimit / k_res);

    ColorRgba m_color;
    ColorRgba m_gradientColor;

    GLuint m_vboReference;
    GLuint m_cbReference;
};

} // namespace graphics
} // namespace core

#endif