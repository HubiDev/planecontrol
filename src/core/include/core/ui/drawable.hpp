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