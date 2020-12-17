#include "game/level.hpp"
#include "core/io/json_helper.hpp"

namespace game
{
Level::Level(const std::string& f_path)
    : m_configFilePath(f_path)
{}

void Level::load() 
{
    core::io::JsonObject json(m_configFilePath);

    
}

} // namespace game
