#include "game/elements/plane_factory.hpp"

namespace game
{
namespace elements
{

PlaneFactory::PlaneFactory()
    : m_planes()
    , m_flightTracks()
{}

PlaneFactory::~PlaneFactory() {}

Plane& PlaneFactory::createPlane()
{
    auto flightTrack_p = std::shared_ptr<FlightTrack>(new FlightTrack());
    auto plane_p = std::shared_ptr<Plane>(new Plane(flightTrack_p));
    m_flightTracks.push_back(flightTrack_p);
    m_planes.push_back(plane_p);
    return *plane_p;
}

} // namespace elements

} // namespace game