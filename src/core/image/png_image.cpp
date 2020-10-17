#include "core/image/png_image.hpp"

extern "C"
{
#include "png.h"
}

#include <exception>
#include <tuple>

namespace core
{
namespace image
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

// All libpng types shall be encapsulated in this compilation unit
// therefore these function implemented in a anonymous namespace
std::tuple<png_struct*, png_info*> initLibPng(std::ifstream& f_imageStream)
{
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
    else
    {
        png_set_read_fn(pngReadStruct_p, &f_imageStream, pngLoadHandler);
    }

    return {pngReadStruct_p, pngInfoStruct_p};
}

void readPngInfo(png_struct* f_pngStruct_p, png_info* f_pngInfo_p, PngImageInfo& f_infoToFill)
{
    png_read_info(f_pngStruct_p, f_pngInfo_p);

    auto ihdrRetVal = png_get_IHDR(f_pngStruct_p,
                                   f_pngInfo_p,
                                   &f_infoToFill.m_width,
                                   &f_infoToFill.m_height,
                                   &f_infoToFill.m_bitDepth,
                                   &f_infoToFill.m_colorType,
                                   &f_infoToFill.m_interlaceMethod,
                                   &f_infoToFill.m_compressionMethod,
                                   &f_infoToFill.m_filterMethod);

    if(ihdrRetVal != 1)
    {
        throw new std::runtime_error("Failed to get PNG info");
    }
}

} // namespace

PngImage::PngImage(const std::string& f_path) noexcept
    : m_info()
    , m_path(f_path)
    , m_imageStream(f_path.c_str(), std::ios_base::binary)
    , m_data()
{}

void PngImage::load()
{
    if(m_imageStream.is_open())
    {
        png_struct* pngReadStruct_p{};
        png_info* pngInfo_p{};

        std::tie(pngReadStruct_p, pngInfo_p) = initLibPng(m_imageStream);

        try
        {
            readPngInfo(pngReadStruct_p, pngInfo_p, m_info);

            auto bytesPerRow = png_get_rowbytes(pngReadStruct_p, pngInfo_p);
            m_data.resize(bytesPerRow * m_info.m_height);

            for(uint32_t i{}; i < m_info.m_height; ++i)
            {
                png_read_row(pngReadStruct_p, &m_data[i * bytesPerRow], nullptr);
            }
        }
        catch(...)
        {
            std::throw_with_nested(std::runtime_error("Failed to load png"));
        }
    }
    else
    {
        throw std::runtime_error("Image does not exist at specified path");
    }
}

std::uint8_t& PngImage::data() noexcept
{
    return m_data.front();
}

std::size_t PngImage::size() noexcept
{
    return (m_info.m_width * m_info.m_height) * (m_info.m_bitDepth / 8);
}

const PngImageInfo& PngImage::info() noexcept
{
    return m_info;
}

} // namespace image
} // namespace core
