#include "game/elements/runway.hpp"
#include "core/graphics/geometry.hpp"

namespace game
{
namespace elements
{
Runway::Runway()
    : core::engine::IGameElement()
    , m_texture_p()
    , m_landingRect_p()
{}

Runway::~Runway() {}

void Runway::load()
{
    m_texture_p =
        std::unique_ptr<core::graphics::Rectangle>(new core::graphics::Rectangle({900.f, 400.f}, {20.f, 100.f}));
    m_landingRect_p =
        std::unique_ptr<core::graphics::Rectangle>(new core::graphics::Rectangle({900.f, 350.f}, {10.f, 10.f}));
}

void Runway::update(const core::engine::UpdateContext& f_context) {}

void Runway::draw()
{
    m_texture_p->draw();
    m_landingRect_p->draw();
}

bool Runway::isPointForLanding(const Vector& f_point)
{
    return core::graphics::geometry::isContainedInRegion(
        m_landingRect_p->getPosition(), m_landingRect_p->getSize(), f_point);
}

} // namespace elements
} // namespace game
