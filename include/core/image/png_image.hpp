#ifndef CORE_IMAGE_PNG_IMAGE_HPP_INCLUDED
#define CORE_IMAGE_PNG_IMAGE_HPP_INCLUDED

#include <cstdint>
#include <string>
#include <vector>
#include <fstream>

namespace core
{
namespace image
{

struct PngImageInfo
{
    std::uint32_t m_width;
    std::uint32_t m_height;
    std::int32_t m_bitDepth;
    std::int32_t m_colorType;
    std::int32_t m_interlaceMethod;
    std::int32_t m_compressionMethod;
    std::int32_t m_filterMethod;
};

class PngImage
{

public:
    /// @brief
    PngImage(const std::string& f_path) noexcept;

    /// @brief
    void load();

    /// @brief
    std::uint8_t& data() noexcept;

    /// @brief
    std::size_t size() noexcept;

    const PngImageInfo& info() noexcept;

private:

    PngImageInfo m_info;
    std::string m_path;
    std::ifstream m_imageStream;
    std::vector<std::uint8_t> m_data;
};

} // namespace image
} // namespace core

#endif