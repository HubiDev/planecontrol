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
#include "game/level.hpp"

#include <iostream>

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
}

void Game::update()
{
    // Move this to seperate function
    for(auto& currentPlane : m_planeFactory.getCreatedPlanes())
    {
        auto landingPathNeedsVerify = currentPlane->landingPathNeedsVerify();

        if(std::get<0>(landingPathNeedsVerify))
        {
            if(m_runway_p->isPointForLanding(std::get<1>(landingPathNeedsVerify)))
            {
                currentPlane->setLandingPath(m_runway_p->getLandingPath());
                currentPlane->finalizeFlightTrack(true);
            }
            else
            {
                currentPlane->finalizeFlightTrack(false);
            }
        }

        if(currentPlane->parkingSlotNeedsVerify())
        {
            auto slot_p = m_runway_p->getLastSelectedParkingSlot();

            if(slot_p)
            {
                int debug = 0;
            }
        }
    }
}

void Game::draw() {}

void Game::loadContent()
{
    // TODO add onBeforeLoad
    Level level("resources/levels/level_01/level.json");
    level.load();
    m_runway_p = level.generateRunway();
    addGameElement(m_runway_p);

    auto plane_p = m_planeFactory.createPlane();
    addGameElement(plane_p->getFlightTrack());
    addGameElement(plane_p);

    GameBase::loadContent();
}

} // namespace game