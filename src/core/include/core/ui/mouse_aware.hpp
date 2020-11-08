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

#ifndef CORE_UI_MOUSE_AWARE_HPP_INCLUDED
#define CORE_UI_MOUSE_AWARE_HPP_INCLUDED

namespace core
{
namespace ui
{

// forward declarations
struct MouseEventArgs;

class IMouseAware
{
public:
    virtual ~IMouseAware() {}

    IMouseAware(const IMouseAware&) = delete;
    IMouseAware(IMouseAware&&) = delete;
    IMouseAware& operator=(const IMouseAware&) = delete;
    IMouseAware& operator=(IMouseAware&&) = delete;

    virtual void onMouseButtonPressed(const MouseEventArgs& f_eventArgs) {}
    virtual void onMouseDown(const MouseEventArgs& f_eventArgs) {}
    virtual void onMouseUp(const MouseEventArgs& f_eventArgs) {}

protected:
    IMouseAware() {}
};

} // namespace ui
} // namespace core

#endif // CORE_UI_MOUSE_AWARE_HPP_INCLUDED
