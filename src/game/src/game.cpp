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

#include "game/game.hpp"

namespace game
{
Game::Game()
    : core::engine::GameBase()
    , m_planeFactory()
    , m_runway_p()
{}

Game::~Game() {}

void Game::onAfterInitialize()
{
    m_runway_p = std::unique_ptr<elements::Runway>(new elements::Runway());
    addGameElement(*m_runway_p);

    auto& plane = m_planeFactory.createPlane();

    // TODO encapsulate this
    plane.setLandingPointFunc(
        [this](const core::graphics::Vector& f_point) -> bool { return m_runway_p->isPointForLanding(f_point); });
    plane.setLandingPath(m_runway_p->getLandingPath());

    addGameElement(plane.getFlightTrack());
    addGameElement(plane);
}

void Game::update() {}

void Game::draw() {}

} // namespace game