#include "game/elements/runway.hpp"

namespace game
{
namespace elements
{
Runway::Runway()
    : core::engine::IGameElement()
    , m_texture_p()
{}

Runway::~Runway() {}

void Runway::load()
{
    m_texture_p =
        std::unique_ptr<core::graphics::Rectangle>(new core::graphics::Rectangle({900.f, 400.f}, {20.f, 100.f}));
}

void Runway::update(const core::engine::UpdateContext& f_context) {}

void Runway::draw() 
{
    m_texture_p->draw();
}

} // namespace elements
} // namespace game
