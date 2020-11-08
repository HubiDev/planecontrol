#ifndef CORE_GRAPHICS_VECTOR_HPP_INCLUDED
#define CORE_GRAPHICS_VECTOR_HPP_INCLUDED

#include <stdint.h>

namespace core
{
namespace graphics
{
struct Vector
{
    float x;
    float y;

    bool operator==(const Vector& toCompare)
    {
        return (x == toCompare.x) && (y == toCompare.y);
    }

    bool operator!=(const Vector& toCompare)
    {
        return !(*this == toCompare);
    }
};

} // namespace graphics
} // namespace core

#endif