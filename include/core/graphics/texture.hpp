#ifndef CORE_GRAPHICS_TEXTURE_HPP_INCLUDED
#define CORE_GRAPHICS_TEXTURE_HPP_INCLUDED

#include "core/image/image.hpp"
#include "core/graphics/vector.hpp"

#include <memory>
#include <string>

namespace core
{
namespace graphics
{
class Texture
{
public:
    Texture(const std::string& f_imagePath);
    void load();
    void draw();

    Vector getSize();
    Vector getPostion();

private:
    std::unique_ptr<image::Image> m_image_p;

    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
};

} // namespace graphics
} // namespace core

#endif