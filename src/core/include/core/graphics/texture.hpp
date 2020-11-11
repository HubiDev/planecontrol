// ------------------------------------------------------------------------
// This file is part of planecontrol.

// planecontrol is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// planecontrol is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with planecontrol.  If not, see <http://www.gnu.org/licenses/>.
// ------------------------------------------------------------------------

#ifndef CORE_GRAPHICS_TEXTURE_HPP_INCLUDED
#define CORE_GRAPHICS_TEXTURE_HPP_INCLUDED

#include "core/graphics/vector.hpp"
#include "core/image/image.hpp"

#include <memory>
#include <string>
#define GL_GLEXT_PROTOTYPES
#include <SDL2/SDL_opengl.h>
#include <array>

namespace core
{
namespace graphics
{
class Texture
{
public:
    Texture(const std::string& f_imagePath, std::tuple<float, float> f_position, std::tuple<float, float> f_size);
    void load();
    void draw();

    Vector getSize();
    Vector getPosition();
    float getRotation();

    void setPosition(float f_posX, float f_posY);
    void setRotation(float f_roatation);
    void setSize(const Vector& f_size);

private:

    void updateRectVertices();

    std::unique_ptr<image::Image> m_image_p;
    std::array<float, 12U> m_rectVertices;

    float m_posX;
    float m_posY;
    float m_width;
    float m_height;
    float m_rotation;

    GLuint m_textureRef;
    GLuint m_rectVertexRef;
    GLuint m_textVertexRef;
};

} // namespace graphics
} // namespace core

#endif