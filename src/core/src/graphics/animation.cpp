#include "core/graphics/animation.hpp"
#include <cmath>
#include <stdexcept>

namespace core
{
namespace graphics
{

Animation::Animation(float f_refStart, float f_refEnd, float f_animationVal)
    : m_refStart(f_refStart)
    , m_refEnd(f_refEnd)
    , m_diff(std::abs(f_refEnd - f_refStart))
    , m_animationVal(f_animationVal)
    , m_lastVal()

{}

float Animation::update(float f_currentRef)
{
    auto currentDiff = std::abs(f_currentRef - m_refStart);
    auto ratio = currentDiff / m_diff;
    auto currentVal = m_animationVal * ratio;

    auto result = currentVal - m_lastVal;
    m_lastVal = result;

    return result;
}

bool Animation::isActive(float f_currentRef)
{
    if(m_refStart < m_refEnd)
    {
        return ((f_currentRef >= m_refStart) && (f_currentRef <= m_refEnd));
    }
    else
    {
        return ((f_currentRef <= m_refStart) && (f_currentRef >= m_refEnd));
    }
}

} // namespace graphics
} // namespace core
