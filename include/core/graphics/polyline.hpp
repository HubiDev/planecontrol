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

    void addPoint(const Vector& f_point);
    void draw();
    void reset();

private:

    void render();
    bool filterPoint(const Vector& f_point);
    
    GLuint m_vboReference;
    float m_thickness;
    std::vector<Vector> m_points;
    std::vector<Vector> m_vertexBuffer;
};

} // namespace graphics

} // namespace core

#endif