#include "core/graphics/image_helper.hpp"
#include <stdexcept>

namespace core
{
namespace graphics
{
void loadPng()
{
    auto* pngReadStruct_p = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if(!pngReadStruct_p)
    {
        throw new std::runtime_error("pnglib read struct creation failure");
    }
}

} // namespace graphics
} // namespace core