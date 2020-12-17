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
        asRef(m_json_p) = strStream.str();
        return true;
    }

    return false;
}

std::string JsonObject::getProperty(const std::string& f_propName)
{
    return asRef(m_json_p)[f_propName].get<std::string>();
}

} // namespace io
} // namespace core