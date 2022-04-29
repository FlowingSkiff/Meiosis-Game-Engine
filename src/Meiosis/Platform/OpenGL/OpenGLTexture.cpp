#include "Meiosis/Platform/OpenGL/OpenGLTexture.hpp"
#include <stb_image.h>
#include "Meiosis/Core/Log.hpp"
namespace Meiosis
{

OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height) : m_path{}, m_is_loaded{ false }, m_width{ width }, m_height{ height }
{
    m_internal_format = GL_RGBA8;
    m_data_format = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
    glTextureStorage2D(m_renderer_id, 1, m_internal_format, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));

    glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
OpenGLTexture2D::OpenGLTexture2D(const std::string& path) : m_path{ path },
                                                            m_is_loaded{ false },
                                                            m_width{ 0 },
                                                            m_height{ 0 },
                                                            m_renderer_id{ 0 },
                                                            m_internal_format{ 0 },
                                                            m_data_format{ 0 }
{
    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        ME_ENGINE_ERROR("Could not load texture file: {}", m_path);
        return;
    }
    m_is_loaded = true;
    m_width = static_cast<uint32_t>(width);
    m_height = static_cast<uint32_t>(height);

    if (channels == 4)
    {
        m_internal_format = GL_RGBA8;
        m_data_format = GL_RGBA;
    }
    else if (channels == 3)
    {
        m_internal_format = GL_RGB8;
        m_data_format = GL_RGB;
    }
    glCreateTextures(GL_TEXTURE_2D, 1, &m_renderer_id);
    glTextureStorage2D(m_renderer_id, 1, m_internal_format, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height));
    glTextureParameteri(m_renderer_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_renderer_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureSubImage2D(m_renderer_id, 0, 0, 0, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height), m_data_format, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
}
OpenGLTexture2D::~OpenGLTexture2D()
{
    glDeleteTextures(1, &m_renderer_id);
}

auto OpenGLTexture2D::getWidth() const -> uint32_t
{
    return m_width;
}
auto OpenGLTexture2D::getHeight() const -> uint32_t
{
    return m_height;
}
auto OpenGLTexture2D::getRendererID() const -> uint32_t
{
    return m_renderer_id;
}

void OpenGLTexture2D::setData(void* data, [[maybe_unused]] uint32_t size)
{
    // TODO: add assert to check size against texture size
    glTextureSubImage2D(m_renderer_id, 0, 0, 0, static_cast<GLsizei>(m_width), static_cast<GLsizei>(m_height), m_data_format, GL_UNSIGNED_BYTE, data);
}
void OpenGLTexture2D::bind(uint32_t slot) const
{
    glBindTextureUnit(slot, m_renderer_id);
}
bool OpenGLTexture2D::isLoaded() const
{
    return m_is_loaded;
}
bool OpenGLTexture2D::operator==(const Texture& other) const
{
    return m_renderer_id == static_cast<const OpenGLTexture2D*>(&other)->m_renderer_id;
}

}// namespace Meiosis