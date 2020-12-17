#ifndef GAME_LEVEL_HPP_INCLUDED
#define GAME_LEVEL_HPP_INCLUDED

#include <string>
#include <vector>

namespace game
{




class Level
{
public:
    Level(const std::string& f_path);
    void load();

private:
    std::string m_configFilePath;
};

} // namespace game

#endif
