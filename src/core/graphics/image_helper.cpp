#include "core/graphics/image_helper.hpp"

#include <stdexcept>
#include <vector>

extern "C"
{
#include "png.h"
}

namespace core
{
namespace graphics
{

namespace
{
    void pngLoadHandler(png_structp f_pngStruct_p, png_bytep f_data_p, png_size_t f_dataSize)
    {

    }
}


void loadPng()
{
    //TODO valudate PNG header

    auto* pngReadStruct_p = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

    if(!pngReadStruct_p)
    {
        throw new std::runtime_error("pnglib read struct creation failure");
    }

    auto* pngInfoStruct_p = png_create_info_struct(pngReadStruct_p);

    if(!pngInfoStruct_p)
    {
        png_destroy_read_struct(&pngReadStruct_p, nullptr, nullptr);
        throw new std::runtime_error("pnglib info struct creation failure");
    }

    // TODO
    std::vector<char> imageData{};

    png_set_read_fn(pngReadStruct_p, imageData.data(), pngLoadHandler);

}

} // namespace graphics
} // namespace core