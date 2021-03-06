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

#include "core/graphics/polyline.hpp"
#include "core/graphics/geometry.hpp"

#include <cassert>
#include <cmath>
#include <iostream>

namespace core
{
namespace graphics
{

Polyline::Polyline(float f_thickness)
    : m_vboReference()
    , m_thickness(f_thickness)
    , m_length()
    , m_points()
    , m_vertexBuffer()
{
    //Create a new VBO and use the variable id to store the VBO id
    glGenBuffers(1, &m_vboReference);
}

Polyline::~Polyline()
{
    glDeleteBuffers(1, &m_vboReference);
}

void Polyline::push_back(const Vector& f_point)
{
    if(m_points.empty())
    {
        m_points.push_back(f_point);
    }
    else
    {
        if(filterPoint(f_point, false))
        {
            m_points.push_back(f_point);

            if(m_points.size() > 1)
            {
                render(); // render the line that was defined by adding the last point
            }
        }
    }
}

void Polyline::push_front(const Vector& f_point)
{
    // TODO add checks

    if(m_points.empty())
    {
        m_points.insert(m_points.begin(), f_point);
    }
    else
    {
        if(filterPoint(f_point, true))
        {
            m_points.insert(m_points.begin(), f_point);

            if(m_points.size() > 1)
            {
                renderFront();
            }
        }
    }
}

void Polyline::beautifySegment()
{
    auto distance = geometry::calcDistance(m_points.back(), m_points.at(m_points.size() - 2));
    distance = std::abs(distance);

    if(distance > 10.f) // TOD define
    {
    }
}

bool Polyline::filterPoint(const Vector& f_point, bool f_front)
{
    // if(!f_front)
    // {
    //     for(std::int32_t i{}; i < m_points.size(); ++i)
    //     {
    //         auto& current = m_points[i];
    //         auto diffX = std::abs(current.x - f_point.x);
    //         auto diffY = std::abs(current.y - f_point.y);

    //         if((diffX < 1.f) || (diffY < 1.f))
    //         {
    //             removePoint(i);
    //         }
    //     }
    // }

    auto& pointToCompare = f_front ? m_points.front() : m_points.back();

    if(pointToCompare != f_point)
    {
        if(geometry::calcDistance(m_points.back(), f_point) > 2.f)
        {
            return true;
        }
    }

    return false;
}

void Polyline::draw()
{
    if(m_vertexBuffer.size() > 0)
    {

        std::vector<float> vertexBuffer;

        for(auto& current : m_vertexBuffer)
        {
            vertexBuffer.push_back(current.x);
            vertexBuffer.push_back(current.y);
            vertexBuffer.push_back(0.f);
        }

        if(vertexBuffer.size() > 0)
        {
            glColor3f(0.4, 0.4, 0.4);

            //Make the new VBO active. Repeat here incase changed since initialisation
            glBindBuffer(GL_ARRAY_BUFFER, m_vboReference);

            //Upload vertex data to the video device
            glBufferData(GL_ARRAY_BUFFER, vertexBuffer.size() * sizeof(float), &vertexBuffer.front(), GL_STATIC_DRAW);

            //Make the new VBO active. Repeat here incase changed since initialisation
            glBindBuffer(GL_ARRAY_BUFFER, m_vboReference);

            //Draw Triangle from VBO - do each time window, view point or data changes
            //Establish its 3 coordinates per vertex with zero stride in this array; necessary here
            glVertexPointer(3, GL_FLOAT, 0, NULL);

            //Establish array contains vertices (not normals, colours, texture coords etc)
            glEnableClientState(GL_VERTEX_ARRAY);

            //Actually draw the triangle, giving the number of vertices provided
            glDrawArrays(GL_TRIANGLES, 0, vertexBuffer.size() / 3);

            glDisableClientState(GL_VERTEX_ARRAY);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    }
}

void Polyline::reset()
{
    m_points.clear();
    m_vertexBuffer.clear();
}

const Vector& Polyline::getPoint(int32_t f_index)
{
    return m_points[f_index];
}

// TODO this is inefficient --> optimize
float Polyline::getLength()
{
    if(m_points.size() > 1)
    {
        float result{};

        for(std::int32_t i{}; i < (m_points.size() - 1); ++i)
        {
            result += geometry::calcDistance(m_points[i], m_points[i + 1]);
        }

        return result;
    }

    return 0.f;
}

// TODO fix
void Polyline::removePoint(int32_t f_index)
{
    int32_t countToDelete = 12;

    m_points.erase(m_points.begin());

    if(m_points.size() > 0) // vertices need not to be removed if more than one point was left
    {
        if(m_vertexBuffer.size() > 12)
        {
            // Delete the point + last line joint
            for(int32_t i = 0; i < countToDelete; ++i)
            {
                //m_vertexBuffer.pop_back();
                m_vertexBuffer.erase(m_vertexBuffer.begin());
            }
        }
        else
        {
            assert(m_vertexBuffer.size() == 6);
            m_vertexBuffer.clear();
        }
    }
}

int32_t Polyline::getPointCount()
{
    return m_points.size();
}

/// @brief This will always render the line to the last point that was added
void Polyline::render()
{
    const auto& startPoint = m_points[m_points.size() - 2];
    const auto& endPoint = m_points.back();

    Vector lowerLeftPoint;
    Vector upperLeftPoint;
    Vector upperRightPoint;
    Vector lowerRightPoint;
    std::tie(lowerLeftPoint, upperLeftPoint, upperRightPoint, lowerRightPoint) = calcLineSegment(startPoint, endPoint);

    if(m_points.size() > 2)
    {
        auto& lastLowerPoint = m_vertexBuffer[m_vertexBuffer.size() - 1];
        auto& lastUpperPoint = m_vertexBuffer[m_vertexBuffer.size() - 2];

        // line joint
        m_vertexBuffer.push_back(lastUpperPoint);
        m_vertexBuffer.push_back(lowerLeftPoint);
        m_vertexBuffer.push_back(upperLeftPoint);

        m_vertexBuffer.push_back(lastLowerPoint);
        m_vertexBuffer.push_back(lowerLeftPoint);
        m_vertexBuffer.push_back(upperLeftPoint);
    }

    // duplicated
    m_vertexBuffer.push_back(lowerLeftPoint);
    m_vertexBuffer.push_back(upperLeftPoint);
    m_vertexBuffer.push_back(lowerRightPoint);

    m_vertexBuffer.push_back(upperLeftPoint);
    m_vertexBuffer.push_back(upperRightPoint);
    m_vertexBuffer.push_back(lowerRightPoint);
}

void Polyline::renderFront()
{
    auto& startPoint = m_points.front();
    auto& endPoint = m_points.at(1);

    Vector lowerLeftPoint;
    Vector upperLeftPoint;
    Vector upperRightPoint;
    Vector lowerRightPoint;
    std::tie(lowerLeftPoint, upperLeftPoint, upperRightPoint, lowerRightPoint) = calcLineSegment(startPoint, endPoint);

    if(m_points.size() > 2)
    {
        auto lastLowerPoint = m_vertexBuffer.at(4);
        auto lastUpperPoint = m_vertexBuffer.at(5);

        // line joint
        m_vertexBuffer.insert(m_vertexBuffer.begin(), lowerRightPoint);
        m_vertexBuffer.insert(m_vertexBuffer.begin(), upperRightPoint);
        m_vertexBuffer.insert(m_vertexBuffer.begin(), lastUpperPoint);

        m_vertexBuffer.insert(m_vertexBuffer.begin(), lowerRightPoint);
        m_vertexBuffer.insert(m_vertexBuffer.begin(), lastUpperPoint);
        m_vertexBuffer.insert(m_vertexBuffer.begin(), lastLowerPoint);
    }

    m_vertexBuffer.insert(m_vertexBuffer.begin(), lowerLeftPoint);
    m_vertexBuffer.insert(m_vertexBuffer.begin(), upperLeftPoint);
    m_vertexBuffer.insert(m_vertexBuffer.begin(), lowerRightPoint);

    m_vertexBuffer.insert(m_vertexBuffer.begin(), upperLeftPoint);
    m_vertexBuffer.insert(m_vertexBuffer.begin(), upperRightPoint);
    m_vertexBuffer.insert(m_vertexBuffer.begin(), lowerRightPoint);
}

std::tuple<Vector, Vector, Vector, Vector> Polyline::calcLineSegment(const Vector& f_startPoint,
                                                                     const Vector& f_endPoint)
{
    Vector vectorBetweenPoints = geometry::calcVector(f_startPoint, f_endPoint);
    Vector orthoVector = geometry::calcOrthoVector(vectorBetweenPoints);
    orthoVector = geometry::calcUnitVector(orthoVector);

    // Calculate all 4 coordinates
    // Start with the upper triangle
    Vector lowerLeftPoint;
    Vector upperLeftPoint;
    Vector upperRightPoint;
    Vector lowerRightPoint;
    lowerLeftPoint.x = f_startPoint.x + ((-1.f) * m_thickness * orthoVector.x);
    lowerLeftPoint.y = f_startPoint.y + ((-1.f) * m_thickness * orthoVector.y);
    upperLeftPoint.x = f_startPoint.x + (m_thickness * orthoVector.x);
    upperLeftPoint.y = f_startPoint.y + (m_thickness * orthoVector.y);
    lowerRightPoint.x = f_endPoint.x + ((-1.f) * m_thickness * orthoVector.x);
    lowerRightPoint.y = f_endPoint.y + ((-1.f) * m_thickness * orthoVector.y);
    upperRightPoint.x = f_endPoint.x + (m_thickness * orthoVector.x);
    upperRightPoint.y = f_endPoint.y + (m_thickness * orthoVector.y);

    return {lowerLeftPoint, upperLeftPoint, upperRightPoint, lowerRightPoint};
}

} // namespace graphics
} // namespace core