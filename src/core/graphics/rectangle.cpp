
#include "core/graphics/rectangle.hpp"

namespace core
{
namespace graphics
{

Rectangle::Rectangle(std::tuple<float, float> f_position, std::tuple<float, float> f_size)
    : m_posX(std::get<0>(f_position))
    , m_posY(std::get<1>(f_position))
    , m_width(std::get<0>(f_size))
    , m_height(std::get<1>(f_size))
{}

Rectangle::~Rectangle() {}

void Rectangle::draw() {}

} // namespace graphics

} // namespace core
