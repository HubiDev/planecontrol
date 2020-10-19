#include "core/graphics/texture.hpp"
#include "core/image/png_image.hpp"

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
{
    glGenTextures(1, &m_textureRef);
}

void Texture::load()
{
    m_image_p->load();
}

void Texture::draw()
{
    glBindTexture(GL_TEXTURE_2D, m_textureRef);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 m_image_p->info().m_width,
                 m_image_p->info().m_height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 &m_image_p->data());
    glBindTexture(GL_TEXTURE_2D, 0);

    //clear and draw quad with texture (could be in display callback)
    glClear(GL_COLOR_ALPHA_PAIRING_ATI);
    glBindTexture(GL_TEXTURE_2D, m_textureRef);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(100, 100);
    glTexCoord2i(0, 1);
    glVertex2i(100, 500);
    glTexCoord2i(1, 1);
    glVertex2i(500, 500);
    glTexCoord2i(1, 0);
    glVertex2i(500, 100);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
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