
#include "core/graphics/rectangle.hpp"
#include <vector>

namespace core
{
namespace graphics
{

Rectangle::Rectangle(std::tuple<float, float> f_position, std::tuple<float, float> f_size)
    : m_posX(std::get<0>(f_position))
    , m_posY(std::get<1>(f_position))
    , m_width(std::get<0>(f_size))
    , m_height(std::get<1>(f_size))
{
    glGenBuffers(1, &m_vboReference);
}

Rectangle::~Rectangle() {}

void Rectangle::draw()
{
    std::vector<float> vertexBuffer;

    // upper left
    vertexBuffer.push_back(m_posX);
    vertexBuffer.push_back(m_posY);
    vertexBuffer.push_back(0.f);

    // upper right
    vertexBuffer.push_back(m_posX + m_width);
    vertexBuffer.push_back(m_posY);
    vertexBuffer.push_back(0.f);

    // lower left
    vertexBuffer.push_back(m_posX);
    vertexBuffer.push_back(m_posY + m_height);
    vertexBuffer.push_back(0.f);

    // lower left
    vertexBuffer.push_back(m_posX);
    vertexBuffer.push_back(m_posY + m_height);
    vertexBuffer.push_back(0.f);

    // lower right
    vertexBuffer.push_back(m_posX + m_width);
    vertexBuffer.push_back(m_posY + m_height);
    vertexBuffer.push_back(0.f);

    // upper right
    vertexBuffer.push_back(m_posX + m_width);
    vertexBuffer.push_back(m_posY);
    vertexBuffer.push_back(0.f);

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

void Rectangle::render() {}

} // namespace graphics

} // namespace core
