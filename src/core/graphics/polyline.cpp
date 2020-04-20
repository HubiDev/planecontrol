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
    , m_vertexBuffer()
{}

Polyline::~Polyline() {}

void Polyline::addPoint(const Coordinate& f_point)
{
    m_points.push_back(f_point);
}

void Polyline::draw()
{
    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.3);
    glVertex3f(10, 10, 0);
    glVertex3f(210, 10, 0);
    glVertex3f(10, 210, 0);
    glEnd();
}

void Polyline::render()
{
    if(m_points.size() > 1)
    {
        for(int32_t i = 0; i < (m_points.size() - 1); ++i)
        {
            auto& startPoint = m_points[i];
            auto& endPoint = m_points[i + 1];

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

            m_vertexBuffer.push_back(pLL);
            m_vertexBuffer.push_back(pUL);
            m_vertexBuffer.push_back(pLR);
            m_vertexBuffer.push_back(pUL);
            m_vertexBuffer.push_back(pUR);
            m_vertexBuffer.push_back(pLR);
        }
    }
}

} // namespace graphics

} // namespace core