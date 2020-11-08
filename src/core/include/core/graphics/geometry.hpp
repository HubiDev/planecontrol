#ifndef CORE_GRAPHICS_GEOMETRY_HPP_INCLUDED
#define CORE_GRAPHICS_GEOMETRY_HPP_INCLUDED

#include "core/graphics/vector.hpp"

namespace core
{
namespace graphics
{
namespace geometry
{

/// @brief
/// @param[in] f_startPoint
/// @param[in] f_endPoint
/// @return
Vector calcVector(const Vector& f_startPoint, const Vector& f_endPoint);

/// @brief
/// @param[in] f_vector
/// @return
Vector calcOrthoVector(const Vector& f_vector);

/// @brief
/// @param[in] f_vector
/// @return
float calcVectorLength(const Vector& f_vector);

/// @brief
/// @param[in] f_vector
/// @return
Vector calcUnitVector(const Vector& f_vector);

float calcDistance(const Vector& f_start, const Vector& f_end);

Vector calcDirection(const Vector& f_start, const Vector& f_end);

float calcAngle(const Vector& f_first, const Vector& f_second);

float calcScalarProduct(const Vector& f_first, const Vector& f_second);

float angleAbs(float f_angle);

bool isContainedInRegion(const Vector& f_origin, const Vector& f_size, const Vector& f_point);

} // namespace geometry
} // namespace graphics
} // namespace core

#endif // CORE_GRAPHICS_GEOMETRY_HPP_INCLUDED