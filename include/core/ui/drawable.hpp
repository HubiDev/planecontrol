#ifndef CORE_UI_DRAWABLE_HPP_INCLUDED
#define CORE_UI_DRAWABLE_HPP_INCLUDED

#include "core/ui/renderer.hpp"

namespace core
{
namespace ui
{
class IDrawable
{    
private:
public:
    virtual ~IDrawable(){};

    IDrawable(const IDrawable&) = delete;
    IDrawable(IDrawable&&) = delete;
    IDrawable& operator=(const IDrawable&) = delete;
    IDrawable& operator=(IDrawable&&) = delete;

    virtual void draw(const Renderer& f_renderer) = 0;

protected:
    IDrawable() {}
};
} // namespace ui

} // namespace core

#endif