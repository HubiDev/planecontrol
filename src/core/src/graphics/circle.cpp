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

// DEBUG
#include <iostream>

namespace core
{
namespace graphics
{
Circle::Circle(const Vector& f_position, float f_radius)
    : m_position(f_position)
    , m_radius(f_radius)
    , m_colorGradient(0.9f)
    , m_vertexBuffer()
    , m_colorBuffer()
    , m_color{0.4f, 0.4f, 0.4f, 1.f}
    , m_vboReference()
    , m_cbReference()
{
    glGenBuffers(1, &m_vboReference);
    glGenBuffers(1, &m_cbReference);
    render();
}

void Circle::draw()
{
    if(m_vertexBuffer.size() > 0)
    {
        //glColor3f(0, 0, 0);
        glClearColor(0, 0, 0, 0);
        glShadeModel(GL_SMOOTH);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboReference);
        glBufferData(GL_ARRAY_BUFFER, m_vertexBuffer.size() * sizeof(float), &m_vertexBuffer.front(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_cbReference);
        glBufferData(GL_ARRAY_BUFFER, m_colorBuffer.size() * sizeof(float), &m_colorBuffer.front(), GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, m_vboReference);
        glVertexPointer(3, GL_FLOAT, 0, NULL);

        glBindBuffer(GL_ARRAY_BUFFER, m_cbReference);
        glColorPointer(4, GL_FLOAT, 0, NULL);

        //Establish array contains vertices (not normals, colours, texture coords etc)
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        //Actually draw the triangle, giving the number of vertices provided
        glDrawArrays(GL_TRIANGLES, 0, m_vertexBuffer.size() / 3);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

const Vector& Circle::getPosition()
{
    return m_position;
}

float Circle::getRadius()
{
    return m_radius;
}

void Circle::render()
{
    constexpr float k_res = 200.f;
    constexpr float k_angleLimit = (2.f * M_PI);
    constexpr float k_segmentSize = (k_angleLimit / k_res);

    //The point (0,r) ends up at x=rsinθ, y=rcosθ.
    float lastX = m_position.x + (m_radius * std::sin(0.f));
    float lastY = m_position.y + (m_radius * std::cos(0.f));
    float lastHalfX = m_position.x + ((m_radius * m_colorGradient) * std::sin(0.f));
    float lastHalfY = m_position.y + ((m_radius * m_colorGradient) * std::cos(0.f));

    float angle{};

    for(float segment{}; segment <= (k_res + std::numeric_limits<float>::epsilon()); segment++)
    {
        float x = m_position.x + (m_radius * std::sin(angle));
        float y = m_position.y + (m_radius * std::cos(angle));
        float halfX = m_position.x + ((m_radius * m_colorGradient) * std::sin(angle));
        float halfY = m_position.y + ((m_radius * m_colorGradient) * std::cos(angle));

        // center
        m_vertexBuffer.push_back(m_position.x);
        m_vertexBuffer.push_back(m_position.y);
        m_vertexBuffer.push_back(0.f);

        // left
        m_vertexBuffer.push_back(lastHalfX);
        m_vertexBuffer.push_back(lastHalfY);
        m_vertexBuffer.push_back(0.f);

        // right
        m_vertexBuffer.push_back(halfX);
        m_vertexBuffer.push_back(halfY);
        m_vertexBuffer.push_back(0.f);

        // outer vertices
        m_vertexBuffer.push_back(lastHalfX);
        m_vertexBuffer.push_back(lastHalfY);
        m_vertexBuffer.push_back(0.f);
        m_vertexBuffer.push_back(lastX);
        m_vertexBuffer.push_back(lastY);
        m_vertexBuffer.push_back(0.f);
        m_vertexBuffer.push_back(halfX);
        m_vertexBuffer.push_back(halfY);
        m_vertexBuffer.push_back(0.f);

        m_vertexBuffer.push_back(lastX);
        m_vertexBuffer.push_back(lastY);
        m_vertexBuffer.push_back(0.f);
        m_vertexBuffer.push_back(x);
        m_vertexBuffer.push_back(y);
        m_vertexBuffer.push_back(0.f);
        m_vertexBuffer.push_back(halfX);
        m_vertexBuffer.push_back(halfY);
        m_vertexBuffer.push_back(0.f);

        renderColor();

        lastX = x;
        lastY = y;
        lastHalfX = halfX;
        lastHalfY = halfY;

        angle += k_segmentSize;
    }
}

void Circle::renderColor()
{
    // inner triangle

    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(m_color.m_a);

    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(m_color.m_a - 0.1f);

    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(m_color.m_a - 0.1f);

    // outer triangles
    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(m_color.m_a - 0.1f);
    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(0.f);
    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(m_color.m_a - 0.1f);

    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(0.f);
    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(0.f);
    m_colorBuffer.push_back(m_color.m_r);
    m_colorBuffer.push_back(m_color.m_g);
    m_colorBuffer.push_back(m_color.m_b);
    m_colorBuffer.push_back(m_color.m_a - 0.1f);
}

} // namespace graphics
} // namespace core