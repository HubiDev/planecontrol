#include "core/graphics/geometry.hpp"
#include <cmath>

namespace core
{
namespace graphics
{
namespace geometry
{

Vector calcVector(const Vector& f_startPoint, const Vector& f_endPoint)
{
    Vector result;
    result.x = (f_endPoint.x - f_startPoint.x);
    result.y = (f_endPoint.y - f_startPoint.y);
    return result;
}

Vector calcOrthoVector(const Vector& f_vector)
{
    Vector result;
    result.x = (f_vector.y * -1.f);
    result.y = f_vector.x;
    return result;
}

float calcVectorLength(const Vector& f_vector)
{
    return std::sqrt(std::pow(f_vector.x, 2.f) + std::pow(f_vector.y, 2.f));
}

Vector calcUnitVector(const Vector& f_vector)
{
    Vector result;
    float length = calcVectorLength(f_vector);
    result.x = (f_vector.x / length);
    result.y = (f_vector.y / length);

    return result;
}

} // namespace geometry
} // namespace graphics
} // namespace core