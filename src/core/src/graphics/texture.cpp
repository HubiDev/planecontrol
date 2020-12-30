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

#include "core/graphics/texture.hpp"
#include "core/io/png_image.hpp"
#include <cmath>

namespace core
{
namespace graphics
{
Texture::Texture(const std::string& f_imagePath, const Vector& f_position, const Vector& f_size)
    : m_image_p(new io::PngImage(f_imagePath))
    , m_posX(f_position.x)
    , m_posY(f_position.y)
    , m_width(f_size.x)
    , m_height(f_size.y)
    , m_rotation(0.f)
    , m_textureRef()
    , m_rectVertexRef()
    , m_textVertexRef()
    , m_rectVertices()
{
    glGenBuffers(1, &m_rectVertexRef);
    glGenBuffers(1, &m_textVertexRef);
    glGenTextures(1, &m_textureRef);
    updateRectVertices();
}

void Texture::load()
{
    m_image_p->load();
}

void Texture::draw()
{
    constexpr std::array<float, 16U> textVertexBuffer = {0.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f};

    glColor3f(1.f, 1.f, 1.f); // take color from texture

    // Load vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_rectVertexRef);
    glBufferData(GL_ARRAY_BUFFER, m_rectVertices.size() * sizeof(float), m_rectVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_textVertexRef);
    glBufferData(GL_ARRAY_BUFFER, textVertexBuffer.size() * sizeof(float), textVertexBuffer.data(), GL_STATIC_DRAW);

    // Load texture
    glBindTexture(GL_TEXTURE_2D, m_textureRef);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 m_image_p->info().m_width,
                 m_image_p->info().m_height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 &m_image_p->data());

    // Render
    glPushMatrix(); // save current matrix
    glTranslatef(m_posX + m_width / 2.f, m_posY + m_height / 2.f, 0.f);
    glRotatef(m_rotation, 0.f, 0.f, 1.f);
    glTranslatef(-(m_posX + m_width / 2.f), -(m_posY + m_height / 2.f), 0.f);

    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, m_rectVertexRef);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, m_textVertexRef);
    glTexCoordPointer(2, GL_FLOAT, 0, NULL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, m_rectVertices.size() / 3);

    // Restore state for next element
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void Texture::setPosition(float f_posX, float f_posY)
{
    m_posX = f_posX;
    m_posY = f_posY;
    updateRectVertices();
}

void Texture::setRotation(float f_rotation)
{
    if(!std::isnan(f_rotation))
    {
        m_rotation = f_rotation;
    }
}

void Texture::setSize(const Vector& f_size)
{
    m_width = f_size.x;
    m_height = f_size.y;
}

Vector Texture::getSize()
{
    return {m_width, m_height};
}

Vector Texture::getPosition()
{
    return {m_posX, m_posY};
}

float Texture::getRotation()
{
    return m_rotation;
}

void Texture::updateRectVertices()
{
    m_rectVertices[0] = m_posX;
    m_rectVertices[1] = m_posY;
    m_rectVertices[2] = 0.f;

    m_rectVertices[3] = m_posX;
    m_rectVertices[4] = m_posY + m_height;
    m_rectVertices[5] = 0.f;

    m_rectVertices[6] = m_posX + m_width;
    m_rectVertices[7] = m_posY + m_height;
    m_rectVertices[8] = 0.f;

    m_rectVertices[9] = m_posX + m_width;
    m_rectVertices[10] = m_posY;
    m_rectVertices[11] = 0.f;
}

} // namespace graphics
} // namespace core