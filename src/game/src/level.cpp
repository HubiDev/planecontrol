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

#include "game/level.hpp"
#include "core/io/json_helper.hpp"
#include "game/elements/runway.hpp"

namespace game
{
Level::Level(const std::string& f_path)
    : m_configFilePath(f_path)
    , m_levelData()
{}

void Level::load()
{
    core::io::JsonObject json(m_configFilePath);

    if(!json.open())
    {
        throw new std::runtime_error("Failed to load level");
    }

    m_levelData = json.deserialize<data::LevelData>();
}

std::shared_ptr<elements::Runway> Level::generateRunway()
{
    std::shared_ptr<elements::Runway> runway_p(new elements::Runway());

    auto locationX = m_levelData.m_airport.m_location[0];
    auto locationY = m_levelData.m_airport.m_location[1];

    // TODO encapsulate
    runway_p->setLocation({locationX, locationY});
    runway_p->setSize({m_levelData.m_airport.m_size[0], m_levelData.m_airport.m_size[1]});
    runway_p->setTexturePath(m_levelData.m_airport.m_texture);

    // TODO encapsulate
    std::vector<core::graphics::Vector> landingPath{};

    for(auto& current : m_levelData.m_airport.m_landingPath)
    {
        landingPath.push_back({locationX + current[0], locationY + current[1]});
    }
    runway_p->setLandingPath(landingPath);

    // TODO encapsulate
    std::vector<core::graphics::Vector> takeoffPath{};

    for(auto& current : m_levelData.m_airport.m_takeoffPath)
    {
        takeoffPath.push_back({locationX + current[0], locationY + current[1]});
    }
    runway_p->setTakeoffPath(takeoffPath);

    // TODO encapsulate
    std::vector<std::shared_ptr<elements::ParkingSlot>> parkingSlots{};

    for(auto& current : m_levelData.m_airport.m_parkingLots)
    {
        std::vector<core::graphics::Vector> parkingPath{};
        std::vector<core::graphics::Vector> startingPath{};

        for(auto& currentPoint : current.m_parkingPath)
        {
            parkingPath.push_back({locationX + currentPoint[0], locationY + currentPoint[1]});
        }

        for(auto& currentPoint : current.m_startingPath)
        {
            startingPath.push_back({locationX + currentPoint[0], locationY + currentPoint[1]});
        }

        parkingSlots.push_back(
            std::shared_ptr<elements::ParkingSlot>(new elements::ParkingSlot(parkingPath, startingPath)));
    }

    runway_p->setParkingSlots(parkingSlots);

    return runway_p;
}

} // namespace game
