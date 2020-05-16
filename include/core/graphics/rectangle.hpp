#ifndef CORE_GRAPHICS_HPP_INCLUDED
#define CORE_GRAPHICS_HPP_INCLUDED

#include "core/graphics/vector.hpp"
#include <tuple>

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
    float m_posX;
    float m_posY;
    float m_width;
    float m_height;

};

} // namespace graphics

} // namespace core

#endif