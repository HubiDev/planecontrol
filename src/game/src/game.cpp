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

void Game::onAfterInitialize() {}

void Game::update()
{
    // Move this to seperate function
    for(auto& currentPlane_p : m_planeFactory.getCreatedPlanes())
    {
        // TODO encapsulate this
        auto landingPathNeedsVerify = currentPlane_p->landingPathNeedsVerify();

        if(std::get<0>(landingPathNeedsVerify))
        {
            if(m_runway_p->isPointForLanding(std::get<1>(landingPathNeedsVerify)))
            {
                currentPlane_p->setLandingPath(m_runway_p->getLandingPath());
                currentPlane_p->finalizeFlightTrack(true);
            }
            else
            {
                currentPlane_p->finalizeFlightTrack(false);
            }
        }

        // TODO encapsulate this
        if(currentPlane_p->parkingSlotNeedsVerify()) // plane was selected
        {
            m_runway_p->setParkingSlotVisible(true);
            auto slot_p = m_runway_p->getLastSelectedParkingSlot(); // slot was selected

            if(slot_p)
            {
                // start parking for this plane
                m_runway_p->registerParking(slot_p, currentPlane_p);
                currentPlane_p->startParking(slot_p->getPathToSlot());
            }
            
        }
        else
        {
            m_runway_p->setParkingSlotVisible(false);
        }

        // TODO encapsulate this
        if(currentPlane_p->startSlotNeedsVerify()) // plane was selected
        {
            m_runway_p->setTakeoffSlotVisible(true);
            if(m_runway_p->takeoffWasSelected())
            {
                auto slot_p = m_runway_p->unregisterParking(currentPlane_p);

                if(slot_p)
                {
                    currentPlane_p->setTakeoffPath(m_runway_p->getTakeoffPath());
                    currentPlane_p->startTakeoff(slot_p->getPathToTakeoff());                    
                }
                else
                {
                    // Game logic error
                }
                
            }
        }
        else
        {
            m_runway_p->setTakeoffSlotVisible(false);
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

    // auto plane2_p = m_planeFactory.createPlane();
    // addGameElement(plane2_p->getFlightTrack());
    // addGameElement(plane2_p);

    GameBase::loadContent();
}

} // namespace game