#include "core/graphics/polyline.hpp"
#include "core/graphics/geometry.hpp"
#include <SDL2/SDL_opengl.h>

namespace core
{
namespace graphics
{

Polyline::Polyline(float f_thickness)
    : m_thickness(f_thickness) // TODO make variable
    , m_points()
    , m_vertexBuffer()
{}

Polyline::~Polyline() {}

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
    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.7);

    for(auto& current : m_vertexBuffer)
    {
        glVertex3f(current.x, current.y, 0.f);
    }

    glEnd();
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