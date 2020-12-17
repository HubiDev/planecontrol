#include "core/io/json_helper.hpp"
#include "nlohmann/json.hpp"

#include <fstream>
#include <sstream>

namespace
{
nlohmann::json& asRef(std::unique_ptr<void, core::io::JsonDeleter>& f_json_p)
{
    return *(static_cast<nlohmann::json*>(f_json_p.get()));
}
} // namespace

namespace core
{
namespace io
{

struct AirportData
{
    std::string texture;
    float location[2];
    float size[2];
    float landing_path[2][2];
    float parking_lots[3][2];
};

struct LevelData
{
    std::string name;
    //AirportData airports[1];
};

void JsonDeleter::operator()(void* f_toDelete_p)
{
    delete static_cast<nlohmann::json*>(f_toDelete_p);
}

JsonObject::JsonObject(const std::string& f_path)
    : m_path(f_path)
    , m_json_p(new nlohmann::json(), JsonDeleter())
{}

bool JsonObject::open()
{
    std::ifstream stream(m_path);

    if(stream.is_open())
    {
        std::stringstream strStream;
        strStream << stream.rdbuf();
        asRef(m_json_p) = nlohmann::json::parse(strStream.str());

        auto tmp = asRef(m_json_p).at("name").get<std::string>();

        return true;
    }

    return false;
}

std::string JsonObject::getProperty(const std::string& f_propName)
{
    return asRef(m_json_p)[f_propName].get<std::string>();
}

float JsonObject::getFloat(const std::string& f_propName)
{
    return asRef(m_json_p)[f_propName].get<float>();
}

} // namespace io
} // namespace core