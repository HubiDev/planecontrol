#ifndef CORE_GRAPHICS_TEXTURE_HPP_INCLUDED
#define CORE_GRAPHICS_TEXTURE_HPP_INCLUDED

#include "core/graphics/vector.hpp"
#include "core/image/image.hpp"

#include <memory>
#include <string>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>

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

    void setPosition(float f_posX, float f_posY);

private:
    std::unique_ptr<image::Image> m_image_p;

    float m_posX;
    float m_posY;
    float m_width;
    float m_height;

    GLuint m_textureRef;
    GLuint m_vertexRef;
};

} // namespace graphics
} // namespace core

#endif