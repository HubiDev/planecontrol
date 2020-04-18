#ifndef CORE_UI_DRAWABLE_HPP_INCLUDED
#define CORE_UI_DRAWABLE_HPP_INCLUDED

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

    virtual void draw() = 0;

protected:
    IDrawable() {}
};
} // namespace ui

} // namespace core

#endif