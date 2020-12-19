#ifndef CORE_IO_JSON_HELPER_HPP_INCLUDED
#define CORE_IO_JSON_HELPER_HPP_INCLUDED

#include <memory>
#include <string>
#include <cstdint>
#include <functional>

#include "nlohmann/json.hpp"

namespace core
{
namespace io
{

class JsonObject
{
public:
    JsonObject(const std::string& f_path);
    bool open();

    template<typename T>
    T deserialize()
    {
        return m_json_p->get<T>();
    }

private:

    std::string m_path;
    std::unique_ptr<nlohmann::json> m_json_p; // void ptr since foward declartion of json type not possible
};

} // namespace io
} // namespace core

#endif
