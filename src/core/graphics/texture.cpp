#include "core/graphics/texture.hpp"
#include "core/image/png_image.hpp"
#include <array>

namespace core
{
namespace graphics
{
Texture::Texture(const std::string& f_imagePath)
    : m_image_p(new image::PngImage(f_imagePath))
    , m_posX()
    , m_posY()
    , m_width()
    , m_height()
    , m_textureRef()
    , m_vertexRef()
{
    glGenBuffers(1, &m_vertexRef);
    glGenTextures(1, &m_textureRef);
}

void Texture::load()
{
    m_image_p->load();
}

void Texture::draw()
{
    std::array<float, 16U> buffer = {0.f,
                                     0.f, //
                                     100.f,
                                     100.f, //
                                     0.f,
                                     1.f,
                                     100.f,
                                     200.f,
                                     1.f,
                                     1.f,
                                     200.f,
                                     200.f,
                                     1.f,
                                     0.f,
                                     200.f,
                                     100.f};

    std::array<float, 12U> tmpBuffer = {100.f,
                                       100.f, //
                                       0.f,
                                       100.f,
                                       200.f,
                                       0.f,
                                       200.f,
                                       200.f,
                                       0.f,
                                       200.f,
                                       100.f,
                                       0.f};

    glColor3f(0.1, 0.2, 0.7);

    // Bind buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexRef);
    glBufferData(GL_ARRAY_BUFFER, tmpBuffer.size() * sizeof(float), tmpBuffer.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexRef);
    // glBindTexture(GL_TEXTURE_2D, m_textureRef);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexImage2D(GL_TEXTURE_2D,
    //              0,
    //              GL_RGBA,
    //              m_image_p->info().m_width,
    //              m_image_p->info().m_height,
    //              0,
    //              GL_RGBA,
    //              GL_UNSIGNED_BYTE,
    //              &m_image_p->data());

    //glBindTexture(GL_TEXTURE_2D, 0);

    //glColor4f(1.f, 1.f, 1.f, 1.f);
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render
    // glEnable(GL_TEXTURE_2D);
    // glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    // glBindBuffer(GL_ARRAY_BUFFER, m_vertexRef);
    // glTexCoordPointer(4, GL_FLOAT, sizeof(float) * 2U, 0);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, tmpBuffer.size() / 3);

    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glBindTexture(GL_TEXTURE_2D, m_textureRef);

    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // glTexImage2D(GL_TEXTURE_2D,
    //              0,
    //              GL_RGBA,
    //              m_image_p->info().m_width,
    //              m_image_p->info().m_height,
    //              0,
    //              GL_RGBA,
    //              GL_UNSIGNED_BYTE,
    //              &m_image_p->data());
    // glBindTexture(GL_TEXTURE_2D, 0);

    // //clear and draw quad with texture (could be in display callback)
    // glBindTexture(GL_TEXTURE_2D, m_textureRef);

    // glColor4f(1.f, 1.f, 1.f, 1.f);
    // glEnable(GL_BLEND);
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // glEnable(GL_TEXTURE_2D);
    // glBegin(GL_QUADS);
    // glTexCoord2i(0, 0);
    // glVertex2i(100, 100);
    // glTexCoord2i(0, 1);
    // glVertex2i(100, 200);
    // glTexCoord2i(1, 1);
    // glVertex2i(200, 200);
    // glTexCoord2i(1, 0);
    // glVertex2i(200, 100);
    // glEnd();
    // glDisable(GL_TEXTURE_2D);
    // glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setPosition(float f_posX, float f_posY)
{
    m_posX = f_posX;
    m_posY = f_posY;
}

Vector Texture::getSize()
{
    return {m_width, m_height};
}

Vector Texture::getPostion()
{
    return {m_posX, m_posY};
}

} // namespace graphics
} // namespace core