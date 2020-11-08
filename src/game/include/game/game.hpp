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

#ifndef GAME_GAME_HPP_INCLUDED
#define GAME_GAME_HPP_INCLUDED

#include "core/engine/game_base.hpp"
#include "game/elements/plane_factory.hpp"
#include "game/elements/runway.hpp"

namespace game
{
class Game : public core::engine::GameBase
{
public:
    Game();
    ~Game();

protected:
    void onAfterInitialize() override;
    void update() override;
    void draw() override;

private:

    elements::PlaneFactory m_planeFactory;
    std::unique_ptr<elements::Runway> m_runway_p;
};

} // namespace game

#endif