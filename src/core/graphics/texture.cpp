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
{}

void Texture::load()
{
    m_image_p->load();
}

void Texture::draw() {}

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