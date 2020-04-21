#include "core/graphics/polyline.hpp"
#include <SDL2/SDL_opengl.h>
#include <cmath>

namespace core
{
namespace graphics
{

Polyline::Polyline()
    : m_thickness(3.f) // TODO make variable
    , m_points()
    , m_upperVertexBuffer()
    , m_lowerVertexBuffer()
{}

Polyline::~Polyline() {}

void Polyline::addPoint(const Coordinate& f_point)
{
    if(m_points.empty())
    {
        m_points.push_back(f_point);
    }
    else
    {
        if((m_points.back().x != f_point.x) || (m_points.back().y != f_point.y))
        {
            m_points.push_back(f_point);

            if(m_points.size() > 1)
            {
                render(); // render the line that was defined by adding the last point
            }
        }
    }
}

void Polyline::draw()
{
    glBegin(GL_TRIANGLES);

    glColor3f(0.1, 0.2, 0.3);

    for(auto& current : m_upperVertexBuffer)
    {
        glVertex3f(current.x, current.y, 0.f);
    }

    glColor3f(0.3, 0.2, 0.1);

    for(auto& current : m_lowerVertexBuffer)
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

    // TODO move this block
    Coordinate vector;
    vector.x = endPoint.x - startPoint.x;
    vector.y = endPoint.y - startPoint.y;

    // Calculate an vector that is orthogonal
    // TODO move this block
    Coordinate orthoVector;
    orthoVector.x = (vector.y * -1.f);
    orthoVector.y = vector.x;

    // Calculate unit vector
    // TODO move this block
    float vectorLength = std::sqrt((orthoVector.x * orthoVector.x) + (orthoVector.y * orthoVector.y));
    orthoVector.x = (orthoVector.x / vectorLength);
    orthoVector.y = (orthoVector.y / vectorLength);

    if(m_points.size() > 2)
    {
        auto& lowerVertex = m_upperVertexBuffer[m_upperVertexBuffer.size() - 1];
        auto& upperVertex = m_upperVertexBuffer[m_upperVertexBuffer.size() - 2];

        Coordinate lastVector;
        lastVector.x = (upperVertex.x - lowerVertex.x) / (2.f * m_thickness);
        lastVector.y = (upperVertex.y - lowerVertex.y) / (2.f * m_thickness);

        Coordinate connectionVector;
        connectionVector.x = lastVector.x + orthoVector.x;
        connectionVector.y = lastVector.y + orthoVector.y;

        // Calculate unit vector
        // TODO move this block
        float connectionVectorLength = std::sqrt((connectionVector.x * connectionVector.x) + (connectionVector.y * connectionVector.y));
        connectionVector.x = (connectionVector.x / connectionVectorLength);
        connectionVector.y = (connectionVector.y / connectionVectorLength);

        // remove vertices that are no longer required
        m_lowerVertexBuffer.pop_back();
        m_upperVertexBuffer.pop_back();
        m_upperVertexBuffer.pop_back();

        // calculate all 6 coordinates
        Coordinate oldUpper;
        Coordinate oldLower;
        oldLower.x = startPoint.x + ((-1) * m_thickness * connectionVector.x);
        oldLower.y = startPoint.y + ((-1) * m_thickness * connectionVector.y);
        oldUpper.x = startPoint.x + (m_thickness * connectionVector.x);
        oldUpper.y = startPoint.y + (m_thickness * connectionVector.y);

        // add the recalculated points
        m_lowerVertexBuffer.push_back(oldLower);
        m_upperVertexBuffer.push_back(oldUpper);
        m_upperVertexBuffer.push_back(oldLower);

        Coordinate pUR;
        Coordinate pLR;
        pLR.x = endPoint.x + ((-1) * m_thickness * orthoVector.x);
        pLR.y = endPoint.y + ((-1) * m_thickness * orthoVector.y);
        pUR.x = endPoint.x + (m_thickness * orthoVector.x);
        pUR.y = endPoint.y + (m_thickness * orthoVector.y);

        m_lowerVertexBuffer.push_back(oldLower);
        m_lowerVertexBuffer.push_back(oldUpper);
        m_lowerVertexBuffer.push_back(pLR);
        m_upperVertexBuffer.push_back(oldUpper);
        m_upperVertexBuffer.push_back(pUR);
        m_upperVertexBuffer.push_back(pLR);
    }
    else
    {
        // Calculate all 4 coordinates
        // Start with the upper triangle
        Coordinate pLL;
        Coordinate pUL;
        Coordinate pUR;
        Coordinate pLR;
        pLL.x = startPoint.x + ((-1) * m_thickness * orthoVector.x);
        pLL.y = startPoint.y + ((-1) * m_thickness * orthoVector.y);
        pUL.x = startPoint.x + (m_thickness * orthoVector.x);
        pUL.y = startPoint.y + (m_thickness * orthoVector.y);
        pLR.x = endPoint.x + ((-1) * m_thickness * orthoVector.x);
        pLR.y = endPoint.y + ((-1) * m_thickness * orthoVector.y);
        pUR.x = endPoint.x + (m_thickness * orthoVector.x);
        pUR.y = endPoint.y + (m_thickness * orthoVector.y);

        m_lowerVertexBuffer.push_back(pLL);
        m_lowerVertexBuffer.push_back(pUL);
        m_lowerVertexBuffer.push_back(pLR);
        m_upperVertexBuffer.push_back(pUL);
        m_upperVertexBuffer.push_back(pUR);
        m_upperVertexBuffer.push_back(pLR);
    }
}

} // namespace graphics

} // namespace core