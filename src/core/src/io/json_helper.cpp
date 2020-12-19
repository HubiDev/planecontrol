#include "core/io/json_helper.hpp"

#include <fstream>
#include <sstream>

namespace core
{
namespace io
{

JsonObject::JsonObject(const std::string& f_path)
    : m_path(f_path)
    , m_json_p(new nlohmann::json())
{}

bool JsonObject::open()
{
    std::ifstream stream(m_path);

    if(stream.is_open())
    {
        std::stringstream strStream;
        strStream << stream.rdbuf();
        (*m_json_p) = nlohmann::json::parse(strStream.str());

        return true;
    }

    return false;
}

} // namespace io
} // namespace core