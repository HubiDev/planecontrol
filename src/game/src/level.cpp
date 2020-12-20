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

    runway_p->setLocation({m_levelData.m_airport.m_location[0], m_levelData.m_airport.m_location[1]});
    runway_p->setSize({m_levelData.m_airport.m_size[0], m_levelData.m_airport.m_size[1]});
    runway_p->setTexturePath(m_levelData.m_airport.m_texture);

    std::vector<core::graphics::Vector> landingPath{};

    for(auto& current : m_levelData.m_airport.m_landingPath)
    {
        landingPath.push_back({current[0], current[1]});
    }

    runway_p->setLandingPath(landingPath);

    return runway_p;
}

} // namespace game
