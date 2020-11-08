#ifndef GAME_ELEMENTS_PLANE_FACTORY_HPP_INCLUDED
#define GAME_ELEMENTS_PLANE_FACTORY_HPP_INCLUDED

#include "game/elements/flight_track.hpp"
#include "game/elements/plane.hpp"
#include <memory>
#include <vector>

namespace game
{
namespace elements
{
class PlaneFactory
{
public:
    PlaneFactory();
    ~PlaneFactory();

    Plane& createPlane();

private:
    std::vector<std::shared_ptr<Plane>> m_planes;
    std::vector<std::shared_ptr<FlightTrack>> m_flightTracks;
};

} // namespace elements

} // namespace game

#endif // GAME_ELEMENTS_PLANE_FACTORY_HPP_INCLUDED
