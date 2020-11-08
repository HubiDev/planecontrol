// ------------------------------------------------------------------------
// This file is part of planecontrol.

// planecontrol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// planecontrol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with planecontrol.  If not, see <http://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------

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
    using namespace std;

    auto scalar = calcScalarProduct(f_first, f_second);
    auto length1 = calcVectorLength(f_first);
    auto length2 = calcVectorLength(f_second);
    auto angleInRadian = ::acosf(scalar / (length1 * length2));
    auto angleInDegree = (angleInRadian * 180.f / M_PI);

    return angleInDegree;
}

float calcScalarProduct(const Vector& f_first, const Vector& f_second)
{
    return (f_first.x * f_second.x) + (f_first.y * f_second.y);
}

float angleAbs(float f_angle)
{
    auto result = std::fmod(f_angle, 360.f);

    if(result < 0.f)
    {
        result += 360.f;
    }

    return result;
}

bool isContainedInRegion(const Vector& f_origin, const Vector& f_size, const Vector& f_point)
{
    if((f_point.x >= f_origin.x) && (f_point.y >= f_origin.y))
    {
        if(((f_origin.x + f_size.x) >= f_point.x) && ((f_origin.y + f_size.y) >= f_point.y))
        {
            return true;
        }
    }

    return false;
}

} // namespace geometry
} // namespace graphics
} // namespace core