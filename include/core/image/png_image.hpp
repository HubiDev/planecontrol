#ifndef CORE_IMAGE_PNG_IMAGE_HPP_INCLUDED
#define CORE_IMAGE_PNG_IMAGE_HPP_INCLUDED

#include "image.hpp"

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>

namespace core
{
namespace image
{

struct PngImageInfo : public ImageInfo
{
    std::int32_t m_colorType;
    std::int32_t m_interlaceMethod;
    std::int32_t m_compressionMethod;
    std::int32_t m_filterMethod;
};

class PngImage : public Image
{

public:
    /// @brief
    PngImage(const std::string& f_path) noexcept;

    /// @brief
    void load() final;

    /// @brief
    std::uint8_t& data() noexcept final;

    /// @brief
    std::size_t size() noexcept final;

    /// @brief
    const ImageInfo& info() noexcept final;

private:

    PngImageInfo m_info;
    std::string m_path;
    std::ifstream m_imageStream;
    std::vector<std::uint8_t> m_data;
};

} // namespace image
} // namespace core

#endif