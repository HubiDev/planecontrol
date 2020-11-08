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

#ifndef CORE_GRAPHICS_POLYLINE_HPP_INCLUDED
#define CORE_GRAPHICS_POLYLINE_HPP_INCLUDED

#include "core/graphics/vector.hpp"

#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>

#include <vector>
#include <tuple>

namespace core
{
namespace graphics
{
class Polyline
{
public:
    Polyline(float f_thickness);
    ~Polyline();

    void push_back(const Vector& f_point);
    void push_front(const Vector& f_point);
    void draw();
    void reset();
    const Vector& getPoint(int32_t f_index);
    void removePoint(int32_t f_index);
    int32_t getPointCount();

private:
    void render();
    void renderFront();
    std::tuple<Vector, Vector, Vector, Vector> calcLineSegment(const Vector& f_startPoint, const Vector& f_endPoint);

    bool filterPoint(const Vector& f_point, bool f_front);
    void beautifySegment();

    GLuint m_vboReference;
    float m_thickness;
    std::vector<Vector> m_points;
    std::vector<Vector> m_vertexBuffer;
};

} // namespace graphics

} // namespace core

#endif