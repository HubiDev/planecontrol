#ifndef CORE_UI_EVENT_MANAGER_HPP_INCLUDED
#define CORE_UI_EVENT_MANAGER_HPP_INCLUDED

namespace core
{
namespace ui
{
class EventManager
{
public:
    EventManager();
    ~EventManager();

    void processEvents();

private:
};
} // namespace ui
} // namespace core

#endif