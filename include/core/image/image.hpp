#ifndef CORE_IMAGE_IMAGE_HPP_INCLUDED
#define CORE_IMAGE_IMAGE_HPP_INCLUDED

#include <cstddef>
#include <cstdint>

namespace core
{
namespace image
{

struct ImageInfo
{
    std::uint32_t m_width;
    std::uint32_t m_height;
    std::int32_t m_bitDepth;
};

class Image
{
public:
    virtual ~Image() = default;
    virtual void load() = 0;
    virtual std::uint8_t& data() noexcept = 0;
    virtual std::size_t size() noexcept = 0;
    virtual const ImageInfo& info() noexcept = 0;
};

} // namespace image
} // namespace core

#endif