#ifndef CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED
#define CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED

#include "core/ui/drawable.hpp"

namespace core
{
namespace engine
{
class IGameElement : public ui::IDrawable
{
public:
    virtual ~IGameElement(){};

    IGameElement(const IGameElement&) = delete;
    IGameElement(IGameElement&&) = delete;
    IGameElement& operator=(const IGameElement&) = delete;
    IGameElement& operator=(IGameElement&&) = delete;

    virtual void update() = 0;

protected:
    IGameElement()
        : ui::IDrawable(){};
};

} // namespace engine

} // namespace core

#endif // CORE_ENGINE_GAME_ELEMENT_HPP_INCLUDED
