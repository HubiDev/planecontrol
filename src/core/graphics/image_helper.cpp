#include "core/graphics/image_helper.hpp"

#include <cstring>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <filesystem>

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
    auto imageStream_p = reinterpret_cast<std::fstream*>(png_get_io_ptr(f_pngStruct_p));

    if(imageStream_p)
    {
        imageStream_p->read(reinterpret_cast<char*>(f_data_p), static_cast<std::streamsize>(f_dataSize));
    }
    else
    {
        throw new std::runtime_error("No image data to load");
    }
}
} // namespace

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

    auto tmp = std::filesystem::exists("");
    std::fstream imageStream("", std::ios_base::binary);

    if(imageStream.is_open())
    {
        png_set_read_fn(pngReadStruct_p, &imageStream, pngLoadHandler);

        png_read_info(pngReadStruct_p, pngInfoStruct_p);
    }
}

} // namespace graphics
} // namespace core