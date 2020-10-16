#include "core/graphics/image_helper.hpp"

#include <cstring>
#include <fstream>
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
    auto imageStream_p = reinterpret_cast<std::ifstream*>(png_get_io_ptr(f_pngStruct_p));

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

    std::ifstream imageStream("", std::ios_base::binary);

    if(imageStream.is_open())
    {
        png_set_read_fn(pngReadStruct_p, &imageStream, pngLoadHandler);

        png_read_info(pngReadStruct_p, pngInfoStruct_p);

        uint32_t width;
        uint32_t height;
        int32_t bitDepth;
        int32_t colorType;
        int32_t interlaceMethod;
        int32_t compressionMethod;
        int32_t filterMethod;

        auto ihdrRetVal = png_get_IHDR(pngReadStruct_p,
                                       pngInfoStruct_p,
                                       &width,
                                       &height,
                                       &bitDepth,
                                       &colorType,
                                       &interlaceMethod,
                                       &compressionMethod,
                                       &filterMethod);

        if(ihdrRetVal != 1)
        {
            // cleanup
            png_destroy_info_struct(pngReadStruct_p, &pngInfoStruct_p);
            png_destroy_read_struct(&pngReadStruct_p, nullptr, nullptr);
            throw new std::runtime_error("Failed to get PNG info");
        }

        if(PNG_COLOR_TYPE_RGB_ALPHA == colorType)
        {
            auto bytesPerRow = png_get_rowbytes(pngReadStruct_p, pngInfoStruct_p);

            std::vector<uint8_t> imageBuffer;
            imageBuffer.resize(bytesPerRow * height);

            for(uint32_t i{}; i < height; ++i)
            {
                png_read_row(pngReadStruct_p, &imageBuffer[i * bytesPerRow], nullptr);
            }
        }
        else
        {
            throw new std::runtime_error("Unsupported image format");
        }
        

        png_destroy_info_struct(pngReadStruct_p, &pngInfoStruct_p);
        png_destroy_read_struct(&pngReadStruct_p, nullptr, nullptr);
    }
}

} // namespace graphics
} // namespace core