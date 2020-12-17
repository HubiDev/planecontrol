#ifndef CORE_IO_JSON_HELPER_HPP_INCLUDED
#define CORE_IO_JSON_HELPER_HPP_INCLUDED

#include <memory>
#include <string>
#include <cstdint>

namespace core
{
namespace io
{

struct JsonDeleter
{
    void operator()(void* f_toDelete_p);
};

class JsonObject
{
public:
    JsonObject(const std::string& f_path);
    bool open();

    std::string getProperty(const std::string& f_propName);
    float getFloat(const std::string& f_propName);

    template<typename T>
    T deserialize()
    {
        
    }

private:
    void freeJson();

    std::string m_path;
    std::unique_ptr<void, JsonDeleter> m_json_p; // void ptr since foward declartion of json type not possible
};

} // namespace io
} // namespace core

#endif
