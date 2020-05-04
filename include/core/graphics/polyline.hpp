#ifndef CORE_GRAPHICS_POLYLINE_HPP_INCLUDED
#define CORE_GRAPHICS_POLYLINE_HPP_INCLUDED

#include "core/graphics/vector.hpp"
#include <vector>

namespace core
{
namespace graphics
{
class Polyline
{
public:
    Polyline(float f_thickness);
    ~Polyline();

    void addPoint(const Vector& f_point);
    void draw();

private:

    void render();
    bool filterPoint(const Vector& f_point);
    
    float m_thickness;
    std::vector<Vector> m_points;
    std::vector<Vector> m_vertexBuffer;
};

} // namespace graphics

} // namespace core

#endif