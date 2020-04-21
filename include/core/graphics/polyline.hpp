#ifndef CORE_GRAPHICS_POLYLINE_HPP_INCLUDED
#define CORE_GRAPHICS_POLYLINE_HPP_INCLUDED

#include "core/graphics/coordinate.hpp"
#include <vector>

namespace core
{
namespace graphics
{
class Polyline
{
public:
    Polyline();
    ~Polyline();

    void addPoint(const Coordinate& f_point);
    void draw();

private:

    void render();
    
    float m_thickness;
    std::vector<Coordinate> m_points;
    std::vector<Coordinate> m_upperVertexBuffer;
    std::vector<Coordinate> m_lowerVertexBuffer;
};

} // namespace graphics

} // namespace core

#endif