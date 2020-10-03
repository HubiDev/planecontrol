#ifndef CORE_GRAPHICS_POLYLINE_HPP_INCLUDED
#define CORE_GRAPHICS_POLYLINE_HPP_INCLUDED

#include "core/graphics/vector.hpp"
#include <vector>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>

namespace core
{
namespace graphics
{
class Polyline
{
public:
    Polyline(float f_thickness);
    ~Polyline();

    void push_back(const Vector& f_point);
    void push_front(const Vector& f_point);
    void draw();
    void reset();
    const Vector& getPoint(int32_t f_index);
    void removePoint(int32_t f_index);
    int32_t getPointCount();

private:
    void render();
    void renderFront();
    std::tuple<Vector, Vector, Vector, Vector> calcLineSegment(const Vector& f_startPoint, const Vector& f_endPoint);

    bool filterPoint(const Vector& f_point);
    void beautifySegment();

    GLuint m_vboReference;
    float m_thickness;
    std::vector<Vector> m_points;
    std::vector<Vector> m_vertexBuffer;
};

} // namespace graphics

} // namespace core

#endif