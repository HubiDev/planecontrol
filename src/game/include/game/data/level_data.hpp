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

#ifndef GAME_DATA_HPP_INCLUDED
#define GAME_DATA_HPP_INCLUDED

#include "core/io/json_helper.hpp"

#include <string>
#include <vector>

namespace game
{
namespace data
{
struct ParkingSlotData
{
    std::vector<std::array<float, 2U>> m_parkingPath;
    std::vector<std::array<float, 2U>> m_startingPath;
};

struct AirportData
{
    std::string m_texture;
    std::array<float, 2U> m_location;
    std::array<float, 2U> m_size;
    std::vector<std::array<float, 2U>> m_landingPath;
    std::vector<ParkingSlotData> m_parkingLots;
};

struct LevelData
{
    std::string m_name;
    AirportData m_airport;
};

inline void to_json(nlohmann::json& f_json, const ParkingSlotData& f_parkingSlotData)
{
    //TODO
}

inline void from_json(const nlohmann::json& f_json, ParkingSlotData& f_parkingSlotData)
{
    f_json.at("parking_path").get_to(f_parkingSlotData.m_parkingPath);
    f_json.at("starting_path").get_to(f_parkingSlotData.m_startingPath);
}

inline void to_json(nlohmann::json& f_json, const AirportData& f_airportData)
{
    //TODO
}

inline void from_json(const nlohmann::json& f_json, AirportData& f_airportData)
{
    f_json.at("texture").get_to(f_airportData.m_texture);
    f_json.at("location").get_to(f_airportData.m_location);
    f_json.at("size").get_to(f_airportData.m_size);
    f_json.at("landing_path").get_to(f_airportData.m_landingPath);
    f_json.at("parking_lots").get_to(f_airportData.m_parkingLots);
}

inline void to_json(nlohmann::json& f_json, const LevelData& f_levelData)
{
    //TODO
}

inline void from_json(const nlohmann::json& f_json, LevelData& f_levelData)
{
    f_json.at("name").get_to(f_levelData.m_name);
    f_json.at("airport").get_to(f_levelData.m_airport);
}

} // namespace data
} // namespace game

#endif