#ifndef CORE_GRAPHICS_TEXTURE_HPP_INCLUDED
#define CORE_GRAPHICS_TEXTURE_HPP_INCLUDED

#include "core/graphics/vector.hpp"
#include "core/image/image.hpp"

#include <memory>
#include <string>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>
#include <array>

namespace core
{
namespace graphics
{
class Texture
{
public:
    Texture(const std::string& f_imagePath, std::tuple<float, float> f_position, std::tuple<float, float> f_size);
    void load();
    void draw();

    Vector getSize();
    Vector getPostion();

    void setPosition(float f_posX, float f_posY);

private:

    void updateRectVertices();

    std::unique_ptr<image::Image> m_image_p;
    std::array<float, 12U> m_rectVertices;

    float m_posX;
    float m_posY;
    float m_width;
    float m_height;

    GLuint m_textureRef;
    GLuint m_rectVertexRef;
    GLuint m_textVertexRef;
};

} // namespace graphics
} // namespace core

#endif