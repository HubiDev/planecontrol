#ifndef GAME_LEVEL_HPP_INCLUDED
#define GAME_LEVEL_HPP_INCLUDED

#include <string>
#include <vector>
#include <memory>

#include "core/engine/game_element.hpp"
#include "game/data/level_data.hpp"
#include "game/elements/runway.hpp"

namespace game
{

class Level
{
public:
    Level(const std::string& f_path);
    void load();
    std::shared_ptr<elements::Runway> generateRunway();

private:
    std::string m_configFilePath;
    data::LevelData m_levelData;
};

} // namespace game

#endif
