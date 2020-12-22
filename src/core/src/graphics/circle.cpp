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

#include "core/graphics/circle.hpp"

#include <cmath>

namespace core
{
namespace graphics
{
Circle::Circle(const Vector& f_position, float f_radius)
    : m_position(f_position)
    , m_radius(f_radius)
    , m_vertexBuffer()
    , m_vboReference()
{
    glGenBuffers(1, &m_vboReference);
    render();
}

void Circle::draw()
{
    if(m_vertexBuffer.size() > 0)
    {
        glColor3f(0.4, 0.4, 0.4);

        //Make the new VBO active. Repeat here incase changed since initialisation
        glBindBuffer(GL_ARRAY_BUFFER, m_vboReference);

        //Upload vertex data to the video device
        glBufferData(GL_ARRAY_BUFFER, m_vertexBuffer.size() * sizeof(float), &m_vertexBuffer.front(), GL_STATIC_DRAW);

        //Make the new VBO active. Repeat here incase changed since initialisation
        glBindBuffer(GL_ARRAY_BUFFER, m_vboReference);

        //Draw Triangle from VBO - do each time window, view point or data changes
        //Establish its 3 coordinates per vertex with zero stride in this array; necessary here
        glVertexPointer(3, GL_FLOAT, 0, NULL);

        //Establish array contains vertices (not normals, colours, texture coords etc)
        glEnableClientState(GL_VERTEX_ARRAY);

        //Actually draw the triangle, giving the number of vertices provided
        glDrawArrays(GL_TRIANGLES, 0, m_vertexBuffer.size() / 3);

        glDisableClientState(GL_VERTEX_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

void Circle::render()
{
    constexpr float k_res = 0.1f;

    //The point (0,r) ends up at x=rsinθ, y=rcosθ.
    float lastX = m_position.x + (m_radius * std::sin(0.f));
    float lastY = m_position.y + (m_radius * std::cos(0.f));

    for(float angle = k_res; angle < (2.f * M_PI); angle += k_res)
    {
        float x = m_position.x + (m_radius * std::sin(angle));
        float y = m_position.y + (m_radius * std::cos(angle));

        // center
        m_vertexBuffer.push_back(m_position.x);
        m_vertexBuffer.push_back(m_position.y);
        m_vertexBuffer.push_back(0.f);

        // left
        m_vertexBuffer.push_back(lastX);
        m_vertexBuffer.push_back(lastY);
        m_vertexBuffer.push_back(0.f);

        // right
        m_vertexBuffer.push_back(x);
        m_vertexBuffer.push_back(y);
        m_vertexBuffer.push_back(0.f);

        lastX = x;
        lastY = y;
    }

    int debug = 0;
}

} // namespace graphics
} // namespace core