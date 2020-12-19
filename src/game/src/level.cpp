#include "game/level.hpp"
#include "core/io/json_helper.hpp"
#include "game/data/level_data.hpp"

namespace game
{
Level::Level(const std::string& f_path)
    : m_configFilePath(f_path)
{}

void Level::load() 
{
    core::io::JsonObject json(m_configFilePath);
    
    if(!json.open())
    {
        throw new std::runtime_error("Failed to load level");
    }

    auto data = json.deserialize<data::LevelData>();
    
    int debug  = 0;
}

} // namespace game
