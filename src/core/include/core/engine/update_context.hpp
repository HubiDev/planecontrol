#ifndef CORE_ENGINE_UPDATE_CONTEXT_HPP_INCLUDED
#define CORE_ENGINE_UPDATE_CONTEXT_HPP_INCLUDED

#include <cstdint>

namespace core
{
namespace engine
{

struct UpdateContext
{
    int64_t m_durationSinceLastUpdate;
}; 

float adaptToFps(const UpdateContext& f_context, float f_toAdapt);

} // namespace engine
} // namespace core

#endif // !CORE_ENGINE_UPDATE_CONTEXT_HPP_INCLUDED