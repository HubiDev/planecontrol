// ------------------------------------------------------------------------
// This file is part of planecontrol.

// planecontrol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// planecontrol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with planecontrol.  If not, see <http://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------

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