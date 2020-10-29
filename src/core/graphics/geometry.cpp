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

float calcDistance(const Vector& f_start, const Vector& f_end)
{
    auto direction = calcDirection(f_start, f_end);
    return calcVectorLength(direction);
}

Vector calcDirection(const Vector& f_start, const Vector& f_end)
{
    return {(f_end.x - f_start.x), (f_end.y - f_start.y)};
}

float calcAngle(const Vector& f_first, const Vector& f_second)
{
    return std::acosf(calcScalarProduct(f_first, f_second) / (calcVectorLength(f_first) * calcVectorLength(f_second)));
}

float calcScalarProduct(const Vector& f_first, const Vector& f_second)
{
    return (f_first.x * f_second.x) + (f_first.y * f_second.y);
}

} // namespace geometry
} // namespace graphics
} // namespace core