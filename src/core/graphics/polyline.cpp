#include "core/graphics/polyline.hpp"
#include "core/graphics/geometry.hpp"

#include <iostream>
#include <cmath>
#include <cassert>

namespace core
{
namespace graphics
{

Polyline::Polyline(float f_thickness)
    : m_vboReference()
    , m_thickness(f_thickness)
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

void Polyline::addPoint(const Vector& f_point)
{
    if(m_points.empty())
    {
        m_points.push_back(f_point);
    }
    else
    {
        if(filterPoint(f_point))
        {
            m_points.push_back(f_point);

            if(m_points.size() > 1)
            {

                render(); // render the line that was defined by adding the last point
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

bool Polyline::filterPoint(const Vector& f_point)
{
    bool result = false;

    if((m_points.back().x != f_point.x) || (m_points.back().y != f_point.y))
    {
        result = true;
    }

    return result;
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
            glColor3f(0.1, 0.2, 0.7);

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

// TODO fix
void Polyline::removePoint(int32_t f_index)
{
    int32_t countToDelete = 12;

    m_points.erase(m_points.begin());

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

int32_t Polyline::getPointCount()
{
    return m_points.size();
}

/// @brief This will always render the line to the last point that was added
void Polyline::render()
{
    auto& startPoint = m_points[m_points.size() - 2];
    auto& endPoint = m_points.back();

    Vector vectorBetweenPoints = geometry::calcVector(startPoint, endPoint);
    Vector orthoVector = geometry::calcOrthoVector(vectorBetweenPoints);
    orthoVector = geometry::calcUnitVector(orthoVector);

    // Calculate all 4 coordinates
    // Start with the upper triangle
    Vector lowerLeftPoint;
    Vector upperLeftPoint;
    Vector upperRightPoint;
    Vector lowerRightPoint;
    lowerLeftPoint.x = startPoint.x + ((-1.f) * m_thickness * orthoVector.x);
    lowerLeftPoint.y = startPoint.y + ((-1.f) * m_thickness * orthoVector.y);
    upperLeftPoint.x = startPoint.x + (m_thickness * orthoVector.x);
    upperLeftPoint.y = startPoint.y + (m_thickness * orthoVector.y);
    lowerRightPoint.x = endPoint.x + ((-1.f) * m_thickness * orthoVector.x);
    lowerRightPoint.y = endPoint.y + ((-1.f) * m_thickness * orthoVector.y);
    upperRightPoint.x = endPoint.x + (m_thickness * orthoVector.x);
    upperRightPoint.y = endPoint.y + (m_thickness * orthoVector.y);

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

    m_vertexBuffer.push_back(lowerLeftPoint);
    m_vertexBuffer.push_back(upperLeftPoint);
    m_vertexBuffer.push_back(lowerRightPoint);
    m_vertexBuffer.push_back(upperLeftPoint);
    m_vertexBuffer.push_back(upperRightPoint);
    m_vertexBuffer.push_back(lowerRightPoint);
}

} // namespace graphics

} // namespace core