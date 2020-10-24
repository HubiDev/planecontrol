#include "core/graphics/texture.hpp"
#include "core/image/png_image.hpp"

namespace core
{
namespace graphics
{
Texture::Texture(const std::string& f_imagePath, std::tuple<float, float> f_position, std::tuple<float, float> f_size)
    : m_image_p(new image::PngImage(f_imagePath))
    , m_posX(std::get<0>(f_position))
    , m_posY(std::get<1>(f_position))
    , m_width(std::get<0>(f_size))
    , m_height(std::get<1>(f_size))
    , m_textureRef()
    , m_rectVertexRef()
    , m_textVertexRef()
    , m_rectVertices()
{
    glGenBuffers(1, &m_rectVertexRef);
    glGenBuffers(1, &m_textVertexRef);
    glGenTextures(1, &m_textureRef);
    updateRectVertices();
}

void Texture::load()
{
    m_image_p->load();
}

void Texture::draw()
{
    constexpr std::array<float, 16U> textVertexBuffer = {0.f,
                                                         0.f, //
                                                         0.f,
                                                         1.f,
                                                         1.f,
                                                         1.f,
                                                         1.f,
                                                         0.f};

    // std::array<float, 12U> rectVertexBuffer = {100.f,
    //                                            100.f, //
    //                                            0.f,
    //                                            100.f,
    //                                            200.f,
    //                                            0.f,
    //                                            200.f,
    //                                            200.f,
    //                                            0.f,
    //                                            200.f,
    //                                            100.f,
    //                                            0.f};

    glColor3f(1.f, 1.f, 1.f);

    // Load vertices
    glBindBuffer(GL_ARRAY_BUFFER, m_rectVertexRef);
    glBufferData(GL_ARRAY_BUFFER, m_rectVertices.size() * sizeof(float), m_rectVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_textVertexRef);
    glBufferData(GL_ARRAY_BUFFER, textVertexBuffer.size() * sizeof(float), textVertexBuffer.data(), GL_STATIC_DRAW);

    // Load texture
    glBindTexture(GL_TEXTURE_2D, m_textureRef);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 m_image_p->info().m_width,
                 m_image_p->info().m_height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 &m_image_p->data());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Render
    glEnable(GL_TEXTURE_2D);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, m_rectVertexRef);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, m_textVertexRef);
    glTexCoordPointer(2, GL_FLOAT, 0, NULL);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_QUADS, 0, m_rectVertices.size() / 3);

    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setPosition(float f_posX, float f_posY)
{
    m_posX = f_posX;
    m_posY = f_posY;
    updateRectVertices();
}

Vector Texture::getSize()
{
    return {m_width, m_height};
}

Vector Texture::getPostion()
{
    return {m_posX, m_posY};
}

void Texture::updateRectVertices()
{
    m_rectVertices[0] = m_posX;
    m_rectVertices[1] = m_posY;
    m_rectVertices[2] = 0.f;

    m_rectVertices[3] = m_posX;
    m_rectVertices[4] = m_posY + m_height;
    m_rectVertices[5] = 0.f;

    m_rectVertices[6] = m_posX + m_width;
    m_rectVertices[7] = m_posY + m_height;
    m_rectVertices[8] = 0.f;

    m_rectVertices[9] = m_posX + m_width;
    m_rectVertices[10] = m_posY;
    m_rectVertices[11] = 0.f;
}

} // namespace graphics
} // namespace core