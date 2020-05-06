#include "core/graphics/polyline.hpp"
#include "core/graphics/geometry.hpp"

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
    glBindBuffer(GL_ARRAY_BUFFER, m_vboReference);
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
    std::vector<float> vertexBuffer;

    for(auto& current : m_vertexBuffer)
    {
        vertexBuffer.push_back(current.x);
        vertexBuffer.push_back(current.y);
        vertexBuffer.push_back(0.f);
    }

    glColor3f(0.1, 0.2, 0.7);

    //Initialise VBO - do only once, at start of program
    //Create a variable to hold the VBO identifier
    //GLuint triangleVBO;

    //Create a new VBO and use the variable id to store the VBO id
    glGenBuffers(1, &m_vboReference);
    //Make the new VBO active
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

    //Force display to be drawn now
    //glFlush();
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