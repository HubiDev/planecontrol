#ifndef GAME_DATA_HPP_INCLUDED
#define GAME_DATA_HPP_INCLUDED

#include "core/io/json_helper.hpp"

#include <string>
#include <vector>

namespace game
{
namespace data
{

struct AirportData
{
    std::string m_texture;
    std::array<float, 2U> m_location;
    std::array<float, 2U> m_size;
    std::vector<std::array<float, 2U>> m_landingPath;
    std::vector<std::array<float, 2U>> m_parkingLots;
};

struct LevelData
{
    std::string m_name;
    AirportData m_airport;
};

void to_json(nlohmann::json& f_json, const AirportData& f_airportData)
{
    //TODO
}

void from_json(const nlohmann::json& f_json, AirportData& f_airportData)
{
    f_json.at("texture").get_to(f_airportData.m_texture);
    f_json.at("location").get_to(f_airportData.m_location);
    f_json.at("size").get_to(f_airportData.m_size);
    f_json.at("landing_path").get_to(f_airportData.m_landingPath);
    f_json.at("parking_lots").get_to(f_airportData.m_parkingLots);
}

void to_json(nlohmann::json& f_json, const LevelData& f_levelData) 
{
    //TODO
}

void from_json(const nlohmann::json& f_json, LevelData& f_levelData)
{
    f_json.at("name").get_to(f_levelData.m_name);
    f_json.at("airport").get_to(f_levelData.m_airport);
}

} // namespace data
} // namespace game

#endif