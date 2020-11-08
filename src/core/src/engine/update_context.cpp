#include "core/engine/update_context.hpp"

namespace core
{
namespace engine
{
float adaptToFps(const UpdateContext& f_context, float f_toAdapt)
{
    constexpr float targetDuration = 1.f / 60.f * 1000.f * 1000.f; // us for one Frame (60 FPS)
    auto ratio = f_context.m_durationSinceLastUpdate / targetDuration;
    return (f_toAdapt * ratio);
}
} // namespace engine
} // namespace core