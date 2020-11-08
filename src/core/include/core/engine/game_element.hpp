#ifndef CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED
#define CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED

#include "core/ui/drawable.hpp"
#include "core/ui/mouse_aware.hpp"

namespace core
{
namespace engine
{

// forward decalrations
class UpdateContext;

class IGameElement : public ui::IDrawable, public ui::IMouseAware
{
public:
    virtual ~IGameElement(){};

    IGameElement(const IGameElement&) = delete;
    IGameElement(IGameElement&&) = delete;
    IGameElement& operator=(const IGameElement&) = delete;
    IGameElement& operator=(IGameElement&&) = delete;

    /// @brief 
    virtual void load() = 0;

    /// @brief
    virtual void update(const UpdateContext& f_context) = 0;

protected:
    inline IGameElement()
        : ui::IDrawable()
        , ui::IMouseAware(){};
};

} // namespace engine
} // namespace core

#endif // CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED
