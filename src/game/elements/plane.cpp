#include "game/elements/plane.hpp"
#include "core/engine/update_context.hpp"
#include "core/graphics/geometry.hpp"
#include <iostream>

namespace game
{
namespace elements
{

Plane::Plane(std::shared_ptr<FlightTrack> f_flightTrack_p)
    : m_flightTrack_p{std::move(f_flightTrack_p)}
    , m_planeTexture_p{}
    , m_speed{2.f}
    , m_textureOrientation{1.f, 0.f} // 90 degrees
{}

Plane::~Plane() {}

/// @brief
void Plane::load()
{
    m_planeTexture_p = std::unique_ptr<core::graphics::Texture>(
        new core::graphics::Texture("resources/textures/plane2.png", {100.f, 100.f}, {100.f, 100.f}));
    m_planeTexture_p->load();
}

/// @brief
void Plane::update(const core::engine::UpdateContext& f_context)
{
    std::cout << f_context.m_durationSinceLastUpdate << std::endl;
    if(m_flightTrack_p->isActive())
    {
        updatePosition();
        updateRotation();
    }
}

void Plane::draw()
{
    m_planeTexture_p->draw();
}

void Plane::onMouseDown(const core::ui::MouseEventArgs& f_eventArgs)
{
    m_flightTrack_p->clear();
    m_flightTrack_p->setActive(true);
}

FlightTrack& Plane::getFlightTrack()
{
    return *m_flightTrack_p;
}

Vector Plane::centrifyPoint(const Vector& f_point)
{
    const float posX = (f_point.x - m_planeTexture_p->getSize().x / 2.f);
    const float posY = (f_point.y - m_planeTexture_p->getSize().y / 2.f);
    return {posX, posY};
}

void Plane::updatePosition()
{
    auto point_p = m_flightTrack_p->moveToNextPoint(m_speed);

    if(point_p)
    {
        auto centrifiedPoint = centrifyPoint(*point_p);
        m_planeTexture_p->setPosition(centrifiedPoint.x, centrifiedPoint.y);
    }
}

void Plane::updateRotation()
{
    auto targetAngle = calcTargetRotation();
    targetAngle = rotateSmooth(targetAngle);

    m_planeTexture_p->setRotation(targetAngle);
}

float Plane::rotateSmooth(float f_targetRotation)
{
    auto currentRotation = m_planeTexture_p->getRotation();
    auto diff = std::abs(currentRotation - f_targetRotation);

    float result{};

    if(diff > 1.f)
    {
        if(currentRotation < f_targetRotation)
        {
            result = (currentRotation + 1.f);
        }
        else
        {
            result = (currentRotation - 1.f);
        }
    }
    else
    {
        result = f_targetRotation;
    }

    return result;
}

float Plane::calcTargetRotation()
{
    auto direction = m_flightTrack_p->getDirection();
    auto angle = core::graphics::geometry::calcAngle(m_textureOrientation, direction);

    if(direction.y < 0.f)
    {
        angle = (360.f - angle);
    }

    angle += 90.f; // Temporary fix for current texture

    return angle;
}

} // namespace elements
} // namespace game
