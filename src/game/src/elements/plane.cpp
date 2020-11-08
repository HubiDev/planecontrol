#include "game/elements/plane.hpp"
#include "core/engine/update_context.hpp"
#include "core/graphics/geometry.hpp"

namespace game
{
namespace elements
{

Plane::Plane(std::shared_ptr<FlightTrack> f_flightTrack_p)
    : m_flightTrack_p{std::move(f_flightTrack_p)}
    , m_planeTexture_p{}
    , m_speed{1.f}
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
    if(m_flightTrack_p->isActive())
    {
        updatePosition(f_context);
        updateRotation(f_context);
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

void Plane::updatePosition(const core::engine::UpdateContext& f_context)
{
    auto adaptedSpeed = core::engine::adaptToFps(f_context, m_speed);
    auto point_p = m_flightTrack_p->moveToNextPoint(adaptedSpeed);

    if(point_p)
    {
        auto centrifiedPoint = centrifyPoint(*point_p);
        m_planeTexture_p->setPosition(centrifiedPoint.x, centrifiedPoint.y);
    }
}

void Plane::updateRotation(const core::engine::UpdateContext& f_context)
{
    auto targetAngle = calcTargetRotation();

    if(!isnan(targetAngle))
    {
        targetAngle = rotateSmooth(targetAngle, f_context);
        m_planeTexture_p->setRotation(targetAngle);
    }
}

float Plane::rotateSmooth(float f_targetRotation, const core::engine::UpdateContext& f_context)
{
    auto currentRotation = m_planeTexture_p->getRotation();

    // todo fix this
    auto diff = std::abs(currentRotation - f_targetRotation);

    float result{};

    if(diff > 0.5f)
    {
        float rotationToDo{};
        float speed = calcRotationSpeed(diff, f_context);

        // turn right by default
        if(currentRotation < f_targetRotation)
        {
            rotationToDo = (diff > 180.f) ? -speed : speed; // check if other direction is shorter
        }
        else // turn left by default
        {
            rotationToDo = (diff > 180.f) ? speed : -speed;
        }

        return core::graphics::geometry::angleAbs(currentRotation + rotationToDo);
    }
    else
    {
        return f_targetRotation;
    }
}

float Plane::calcTargetRotation()
{
    auto direction = m_flightTrack_p->getDirection();
    auto angle = core::graphics::geometry::calcAngle(m_textureOrientation, direction);

    if(direction.y < 0.f)
    {
        angle = (360.f - angle);
    }

    // Temporary fix for current texture
    angle = core::graphics::geometry::angleAbs(angle + 90.f);

    return angle;
}

float Plane::calcRotationSpeed(float f_angleDiff, const core::engine::UpdateContext& f_context)
{
    constexpr float speedDivisor = 10.f;
    constexpr float maxSpeed = 5.f;
    float result{};

    if(f_angleDiff > 180.f)
    {
        result = (f_angleDiff - 180.f) / speedDivisor;
    }
    else
    {
        result = f_angleDiff / speedDivisor;
    }

    if(result > maxSpeed)
    {
        result = maxSpeed;
    }

    return core::engine::adaptToFps(f_context, result);
}

} // namespace elements
} // namespace game
