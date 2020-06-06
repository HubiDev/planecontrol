#ifndef CORE_GRAPHICS_HPP_INCLUDED
#define CORE_GRAPHICS_HPP_INCLUDED

#include "core/graphics/vector.hpp"
#include <array>
#include <tuple>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>

namespace core
{
namespace graphics
{

class Rectangle
{
public:
    Rectangle(std::tuple<float, float> f_position, std::tuple<float, float> f_size);
    ~Rectangle();

    void draw();

private:
    void render();

    float m_posX;
    float m_posY;
    float m_width;
    float m_height;

    GLuint m_vboReference;
    std::array<float, 6U> m_vertexBuffer;
};

} // namespace graphics

} // namespace core

#endif