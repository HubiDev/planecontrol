#include "core/graphics/polyline.hpp"

namespace core
{
namespace graphics
{

Polyline::Polyline() {}

Polyline::~Polyline() {}

void Polyline::addPoint(const Coordinate& f_point)
{
    m_points.push_back(f_point);
}

} // namespace graphics

} // namespace core